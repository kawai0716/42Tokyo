# Executor（実行エンジン）設計

## 1. 概要

実行エンジンはパーサーが生成したAST（抽象構文木）を解釈し、実際のコマンド実行を行います。プロセス管理、パイプライン処理、リダイレクション、ビルトインコマンドの実行などを担当します。

## 2. 実行エンジンのアーキテクチャ

### 2.1 コンポーネント構成

```
executor/
├── execute.c          # メイン実行ロジック
├── cmd_exec.c         # 外部コマンド実行
├── cmd_path.c         # PATH解決
├── pipe.c             # パイプライン基本処理
├── pipe_exec.c        # パイプ実行処理
├── pipe_builtin.c     # パイプ内ビルトイン処理
├── pipe_redir.c       # パイプ内リダイレクション
├── pipe_error.c       # パイプエラー処理
├── redirect.c         # リダイレクション処理
├── heredoc.c          # ヒアドキュメント処理
├── heredoc_utils.c    # ヒアドキュメントユーティリティ
├── assignment.c       # 変数代入処理
├── assignment_utils.c # 変数代入ユーティリティ
├── exec_error.c       # 実行エラー処理
└── utils.c            # 共通ユーティリティ

builtin/
├── builtin_echo.c     # echoコマンド
├── builtin_cd.c       # cdコマンド
├── builtin_cd_utils.c # cdユーティリティ
├── builtin_pwd.c      # pwdコマンド
├── builtin_export.c   # exportコマンド
├── builtin_export_utils.c # exportユーティリティ
├── builtin_unset.c    # unsetコマンド
├── builtin_env.c      # envコマンド
├── builtin_exit.c     # exitコマンド
├── builtin_exit_utils.c # exitユーティリティ
└── builtin_utils.c    # 共通ユーティリティ
```

### 2.2 実行フロー

```
AST
 ↓
ノード種別判定
 ↓
┌─────────────────┬──────────────┬──────────────┬────────────┐
│    NODE_CMD     │  NODE_PIPE   │ NODE_REDIR   │NODE_SEMICOLON│
├─────────────────┼──────────────┼──────────────┼────────────┤
│ ビルトイン判定  │ パイプ作成   │ FD設定       │ 順次実行   │
│      ↓          │      ↓       │     ↓        │     ↓      │
│ 内部/外部実行   │ fork×2      │ 実行         │ 左→右実行  │
└─────────────────┴──────────────┴──────────────┴────────────┘
```

## 3. コマンド実行

### 3.1 ビルトインコマンド

```c
typedef struct s_builtin {
    char    *name;
    int     (*func)(char **argv, t_shell *shell);
} t_builtin;

static t_builtin builtins[] = {
    {"echo", builtin_echo},
    {"cd", builtin_cd},
    {"pwd", builtin_pwd},
    {"export", builtin_export},
    {"unset", builtin_unset},
    {"env", builtin_env},
    {"exit", builtin_exit},
    {NULL, NULL}
};
```

### 3.2 外部コマンド実行

```c
void execute_external_command(t_node *cmd, t_shell *shell) {
    pid_t pid = fork();
    
    if (pid == 0) {  // 子プロセス
        // PATH解決
        char *path = resolve_command_path(cmd->u_data.cmd.argv[0], shell);
        
        // 実行
        execve(path, cmd->u_data.cmd.argv, shell->env);
        
        // エラー処理
        handle_exec_error(cmd->u_data.cmd.argv[0]);
        exit(127);
    } else if (pid > 0) {  // 親プロセス
        int status;
        waitpid(pid, &status, 0);
        update_exit_status(status, shell);
    }
}
```

### 3.3 PATH解決

```c
char *resolve_command_path(char *cmd, t_shell *shell) {
    // 絶対パス・相対パスの場合
    if (ft_strchr(cmd, '/'))
        return cmd;
    
    // PATH環境変数から検索
    char *path_env = getenv("PATH");
    char **paths = ft_split(path_env, ':');
    
    for (int i = 0; paths[i]; i++) {
        char *full_path = build_full_path(paths[i], cmd);
        if (access(full_path, X_OK) == 0)
            return full_path;
    }
    
    return NULL;
}
```

## 4. パイプライン処理

### 4.1 パイプの作成と管理

```c
void execute_pipeline(t_node *pipe_node, t_shell *shell) {
    int pipefd[2];
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }
    
    pid_t pid1 = fork();
    if (pid1 == 0) {  // 左側のコマンド
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execute_node(pipe_node->u_data.pipe.left, shell);
        exit(shell->exit_status);
    }
    
    pid_t pid2 = fork();
    if (pid2 == 0) {  // 右側のコマンド
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execute_node(pipe_node->u_data.pipe.right, shell);
        exit(shell->exit_status);
    }
    
    // 親プロセス
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
}
```

### 4.2 複数パイプの処理

```c
// パイプチェーンの処理
void execute_pipe_chain(t_list *commands, t_shell *shell) {
    int prev_pipe[2] = {-1, -1};
    int curr_pipe[2];
    
    for (int i = 0; i < list_size(commands); i++) {
        // 最後のコマンドでなければパイプ作成
        if (i < list_size(commands) - 1) {
            if (pipe(curr_pipe) == -1)
                handle_pipe_error();
        }
        
        pid_t pid = fork();
        if (pid == 0) {
            // 前のパイプから入力
            if (prev_pipe[0] != -1) {
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            
            // 次のパイプへ出力
            if (i < list_size(commands) - 1) {
                dup2(curr_pipe[1], STDOUT_FILENO);
                close(curr_pipe[0]);
                close(curr_pipe[1]);
            }
            
            execute_command(list_get(commands, i), shell);
            exit(shell->exit_status);
        }
        
        // パイプの更新
        if (prev_pipe[0] != -1) {
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        prev_pipe[0] = curr_pipe[0];
        prev_pipe[1] = curr_pipe[1];
    }
}
```

## 5. リダイレクション処理

### 5.1 ファイルディスクリプタ管理

```c
int apply_redirection(t_node *redir, t_shell *shell) {
    int fd = -1;
    
    switch (redir->u_data.redir.redir_type) {
        case REDIR_IN:  // <
            fd = open(redir->u_data.redir.filename, O_RDONLY);
            if (fd < 0) {
                print_error("No such file or directory");
                return -1;
            }
            dup2(fd, STDIN_FILENO);
            break;
            
        case REDIR_OUT:  // >
            fd = open(redir->u_data.redir.filename, 
                     O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            break;
            
        case REDIR_APPEND:  // >>
            fd = open(redir->u_data.redir.filename,
                     O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            break;
            
        case HEREDOC:  // <<
            fd = redir->u_data.redir.heredoc_fd;
            dup2(fd, STDIN_FILENO);
            break;
    }
    
    if (fd > 2)
        close(fd);
    
    return 0;
}
```

### 5.2 複数リダイレクション

```c
// 複数のリダイレクションを順番に適用
int apply_all_redirections(t_node **redirs, int count) {
    for (int i = 0; i < count; i++) {
        if (apply_redirection(redirs[i]) < 0)
            return -1;
    }
    return 0;
}
```

## 6. ヒアドキュメント処理

### 6.1 ヒアドキュメントの実装

```c
int read_heredoc_to_pipe(const char *delimiter, t_shell *shell) {
    int pipefd[2];
    
    if (pipe(pipefd) == -1)
        return -1;
    
    // インタラクティブモードの場合はfork
    if (isatty(STDIN_FILENO)) {
        pid_t pid = fork();
        if (pid == 0) {
            // 子プロセスで入力を読み取り
            close(pipefd[0]);
            setup_heredoc_signals();
            
            char *line;
            while ((line = readline("> "))) {
                if (strcmp(line, delimiter) == 0) {
                    free(line);
                    break;
                }
                write(pipefd[1], line, strlen(line));
                write(pipefd[1], "\n", 1);
                free(line);
            }
            
            close(pipefd[1]);
            exit(0);
        }
        
        // 親プロセス
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
        return pipefd[0];
    } else {
        // 非インタラクティブモード
        process_heredoc_loop(pipefd, delimiter, shell);
        close(pipefd[1]);
        return pipefd[0];
    }
}
```

### 6.2 シグナル処理との連携

```c
static void setup_heredoc_signals(void) {
    struct sigaction sa;
    
    // Ctrl+Cでヒアドキュメント入力を中断
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}
```

## 7. 変数代入処理

### 7.1 代入の識別と処理

```c
// 変数代入の判定（VAR=value形式）
int is_assignment(const char *str) {
    if (!str || !*str)
        return 0;
    
    // 最初の文字が英字またはアンダースコア
    if (!ft_isalpha(*str) && *str != '_')
        return 0;
    
    // '='までの文字が有効な変数名か確認
    while (*str && *str != '=') {
        if (!ft_isalnum(*str) && *str != '_')
            return 0;
        str++;
    }
    
    return (*str == '=');
}
```

### 7.2 環境変数への設定

```c
int process_assignment(const char *str, t_shell *shell) {
    char *equal = ft_strchr(str, '=');
    char *key = ft_substr(str, 0, equal - str);
    char *value = ft_strdup(equal + 1);
    
    set_env_value(&shell->env_list, key, value);
    
    free(key);
    free(value);
    return 0;
}
```

## 8. プロセス管理

### 8.1 子プロセスの作成と待機

```c
typedef struct s_process {
    pid_t   pid;
    int     status;
    int     completed;
} t_process;

void wait_for_children(t_process *processes, int count, t_shell *shell) {
    for (int i = 0; i < count; i++) {
        if (processes[i].pid > 0) {
            waitpid(processes[i].pid, &processes[i].status, 0);
            processes[i].completed = 1;
        }
    }
    
    // 最後のプロセスの終了ステータスを保存
    if (count > 0) {
        update_exit_status(processes[count-1].status, shell);
    }
}
```

### 7.2 終了ステータス管理

```c
void update_exit_status(int status, t_shell *shell) {
    if (WIFEXITED(status)) {
        shell->exit_status = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        shell->exit_status = 128 + WTERMSIG(status);
    }
}
```

## 8. エラー処理

### 8.1 実行エラーの種類

```c
#define ERROR_CMD_NOT_FOUND 127  // コマンドが見つからない
#define ERROR_EXEC          126  // 実行権限がない
#define ERROR_FORK          254  // fork失敗
#define ERROR_PIPE          128  // pipe失敗
```

### 8.2 エラーメッセージ

```c
void handle_exec_error(char *cmd, int error_type) {
    switch (error_type) {
        case ERROR_CMD_NOT_FOUND:
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd, 2);
            ft_putstr_fd(": command not found\n", 2);
            break;
        case ERROR_EXEC:
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd, 2);
            ft_putstr_fd(": Permission denied\n", 2);
            break;
        // 他のエラー...
    }
}
```

## 9. ビルトインコマンドの実装

### 9.1 echo

```c
int builtin_echo(char **argv, t_shell *shell) {
    int n_flag = 0;
    int i = 1;
    
    // -nオプションの処理
    if (argv[i] && strcmp(argv[i], "-n") == 0) {
        n_flag = 1;
        i++;
    }
    
    // 引数を出力
    while (argv[i]) {
        printf("%s", argv[i]);
        if (argv[i + 1])
            printf(" ");
        i++;
    }
    
    if (!n_flag)
        printf("\n");
    
    return 0;
}
```

### 9.2 cd

```c
int builtin_cd(char **argv, t_shell *shell) {
    char *path;
    
    if (!argv[1] || strcmp(argv[1], "~") == 0) {
        path = getenv("HOME");
        if (!path) {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return 1;
        }
    } else {
        path = argv[1];
    }
    
    if (chdir(path) != 0) {
        perror("cd");
        return 1;
    }
    
    // PWDとOLDPWDの更新
    update_pwd_env(shell);
    
    return 0;
}
```

## 10. 最適化

### 10.1 ビルトインコマンドのfork回避

```c
// 単独のビルトインコマンドはforkせずに実行
if (is_single_builtin(node)) {
    return execute_builtin_no_fork(node, shell);
}
```

### 10.2 ファイルディスクリプタの効率的管理

```c
// FDテーブルによる管理
typedef struct s_fd_manager {
    int saved_stdin;
    int saved_stdout;
    int saved_stderr;
} t_fd_manager;
```

## 11. テストと検証

### 11.1 実行テスト

- 基本的なコマンド実行
- パイプライン動作
- リダイレクション動作
- ビルトインコマンド動作
- エラーケース

### 11.2 メモリリークチェック

```bash
valgrind --leak-check=full ./minishell
```