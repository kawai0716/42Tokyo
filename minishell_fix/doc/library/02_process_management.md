# プロセス管理関数

## fork

### プロトタイプ
```c
pid_t fork(void);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
現在のプロセスの複製（子プロセス）を作成します。

### 戻り値
- 親プロセス: 子プロセスのPID（正の値）
- 子プロセス: 0
- エラー時: -1（errnoが設定される）

### Minishellでの使用例

#### 基本的な使用
```c
// src/executor/cmd_exec.c
void execute_external_command(char **argv, t_shell *shell)
{
    pid_t pid;
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        shell->exit_status = 1;
        return;
    }
    if (pid == 0)
    {
        // 子プロセス
        execve(cmd_path, argv, shell->envp);
        perror("execve");
        exit(127);
    }
    else
    {
        // 親プロセス
        int status;
        waitpid(pid, &status, 0);
        update_exit_status(status, shell);
    }
}
```

#### パイプライン処理
```c
// src/executor/pipe.c
void execute_pipeline(t_node *pipe_node, t_shell *shell)
{
    int     pipefd[2];
    pid_t   pid1, pid2;
    
    if (pipe(pipefd) == -1)
        return handle_pipe_error(shell);
    
    pid1 = fork();
    if (pid1 == 0)
    {
        // 第1子プロセス（左側コマンド）
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execute_node(pipe_node->u_data.pipe.left, shell);
        exit(shell->exit_status);
    }
    
    pid2 = fork();
    if (pid2 == 0)
    {
        // 第2子プロセス（右側コマンド）
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execute_node(pipe_node->u_data.pipe.right, shell);
        exit(shell->exit_status);
    }
    
    // 親プロセス
    close(pipefd[0]);
    close(pipefd[1]);
    wait_for_children(pid1, pid2, shell);
}
```

### 注意点
- **メモリとファイルディスクリプタ**: 子プロセスは親のメモリ空間とFDをコピー
- **シグナルハンドラ**: 子プロセスでリセットが必要な場合あり
- **エラー処理**: fork失敗時の適切な処理が重要

---

## execve

### プロトタイプ
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
現在のプロセスイメージを新しいプログラムで置き換えます。

### パラメータ
- `pathname`: 実行するプログラムのパス
- `argv`: 引数配列（NULL終端）
- `envp`: 環境変数配列（NULL終端）

### 戻り値
- 成功時: 戻らない（プロセスが置き換わる）
- 失敗時: -1（errnoが設定される）

### Minishellでの使用例

#### 外部コマンド実行
```c
// src/executor/cmd_exec.c
void exec_external(char *cmd_path, char **argv, char **envp)
{
    // 子プロセスでシグナルをリセット
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    
    execve(cmd_path, argv, envp);
    
    // execveが戻ってきた場合はエラー
    perror(argv[0]);
    if (errno == ENOENT)
        exit(127);  // Command not found
    else if (errno == EACCES)
        exit(126);  // Permission denied
    else
        exit(1);    // その他のエラー
}
```

#### PATH検索との組み合わせ
```c
// src/executor/cmd_path.c
char *find_cmd_path(const char *cmd, t_shell *shell)
{
    char    *path_env;
    char    **paths;
    char    *full_path;
    int     i;
    
    // 絶対パスまたは相対パスの場合
    if (strchr(cmd, '/'))
        return (strdup(cmd));
    
    // PATH環境変数から検索
    path_env = get_env_value(shell->env_list, "PATH");
    if (!path_env)
        return (NULL);
    
    paths = ft_split(path_env, ':');
    i = 0;
    while (paths[i])
    {
        full_path = build_path(paths[i], cmd);
        if (access(full_path, X_OK) == 0)
        {
            free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_split(paths);
    return (NULL);
}
```

### エラーコードと終了ステータス
| errno | 終了ステータス | 意味 |
|-------|---------------|------|
| ENOENT | 127 | コマンドが見つからない |
| EACCES | 126 | 実行権限がない |
| その他 | 1 | 一般的なエラー |

---

## waitpid

### プロトタイプ
```c
pid_t waitpid(pid_t pid, int *wstatus, int options);
```

### ヘッダファイル
```c
#include <sys/wait.h>
```

### 説明
指定した子プロセスの終了を待機します。

### パラメータ
- `pid`: 待機する子プロセスのPID（-1で任意の子プロセス）
- `wstatus`: 終了ステータスを格納する変数へのポインタ
- `options`: 動作オプション（0で通常のブロッキング待機）

### 戻り値
- 成功時: 終了した子プロセスのPID
- エラー時: -1

### Minishellでの使用例

#### 単一プロセスの待機
```c
// src/executor/execute.c
void wait_for_child(pid_t pid, t_shell *shell)
{
    int status;
    
    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        return;
    }
    
    // 終了ステータスの解析
    if (WIFEXITED(status))
    {
        // 正常終了
        shell->exit_status = WEXITSTATUS(status);
    }
    else if (WIFSIGNALED(status))
    {
        // シグナルによる終了
        int sig = WTERMSIG(status);
        shell->exit_status = 128 + sig;
        
        if (sig == SIGQUIT)
            write(STDERR_FILENO, "Quit: 3\n", 8);
        else if (sig == SIGINT)
            write(STDERR_FILENO, "\n", 1);
    }
}
```

#### 複数プロセスの待機（パイプライン）
```c
// src/executor/pipe.c
void wait_for_pipeline(pid_t pid1, pid_t pid2, t_shell *shell)
{
    int status1, status2;
    
    // 両方の子プロセスを待機
    waitpid(pid1, &status1, 0);
    waitpid(pid2, &status2, 0);
    
    // 最後のコマンドの終了ステータスを保存
    if (WIFEXITED(status2))
        shell->exit_status = WEXITSTATUS(status2);
    else if (WIFSIGNALED(status2))
        shell->exit_status = 128 + WTERMSIG(status2);
}
```

### ステータスマクロ
| マクロ | 説明 |
|--------|------|
| WIFEXITED(status) | 正常終了したか |
| WEXITSTATUS(status) | 終了コード取得 |
| WIFSIGNALED(status) | シグナルで終了したか |
| WTERMSIG(status) | 終了シグナル番号取得 |

---

## exit

### プロトタイプ
```c
void exit(int status);
```

### ヘッダファイル
```c
#include <stdlib.h>
```

### 説明
プロセスを終了し、親プロセスに終了ステータスを返します。

### パラメータ
- `status`: 終了ステータス（0-255の範囲）

### Minishellでの使用例

#### ビルトインexitコマンド
```c
// src/builtin/builtin_exit.c
int builtin_exit(char **argv, t_shell *shell)
{
    long exit_code;
    int overflow;
    
    // 引数なしの場合
    if (!argv[1])
    {
        shell->should_exit = 1;
        return (shell->exit_status);
    }
    
    // 数値引数の解析
    exit_code = custom_atol(argv[1], &overflow);
    
    if (overflow || !is_numeric(argv[1]))
    {
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit(255);
    }
    
    // 引数が多すぎる場合
    if (argv[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1);
    }
    
    shell->should_exit = 1;
    shell->exit_status = (int)(exit_code & 0xFF);
    return (shell->exit_status);
}
```

#### 子プロセスでのエラー終了
```c
// src/executor/cmd_exec.c
void handle_exec_error(char *cmd)
{
    if (errno == ENOENT)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    else if (errno == EACCES)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": Permission denied\n", 2);
        exit(126);
    }
    else
    {
        perror("minishell");
        exit(1);
    }
}
```

### 終了ステータスの慣例
| ステータス | 意味 |
|-----------|------|
| 0 | 成功 |
| 1 | 一般的なエラー |
| 2 | ビルトインの使用法エラー |
| 126 | コマンド実行不可（権限なし） |
| 127 | コマンドが見つからない |
| 128+n | シグナルnで終了 |
| 255 | 無効な終了引数 |

## プロセス管理のベストプラクティス

### 1. fork前の準備
```c
// パイプやファイルディスクリプタの準備
int pipefd[2];
if (pipe(pipefd) == -1)
    return handle_error();

// fork前にシグナルマスクの設定
```

### 2. 子プロセスでの処理
```c
if (pid == 0)
{
    // 1. 不要なFDを閉じる
    close_unused_fds();
    
    // 2. シグナルハンドラをリセット
    reset_signals();
    
    // 3. FDのリダイレクション
    setup_redirections();
    
    // 4. execveまたはビルトイン実行
    execute_command();
    
    // 5. 必ずexitで終了
    exit(exit_status);
}
```

### 3. 親プロセスでの処理
```c
// 1. 不要なFDを即座に閉じる
close(pipefd[1]);

// 2. 子プロセスを待機
wait_for_child(pid);

// 3. 終了ステータスを適切に処理
handle_exit_status(status);
```

### 4. エラー処理
- fork失敗時のリカバリー
- execve失敗時の適切な終了コード
- waitpid失敗時の処理

### 5. リソース管理
- ゾンビプロセスの防止（必ずwait）
- ファイルディスクリプタのリーク防止
- メモリリークの防止（子プロセスでも）