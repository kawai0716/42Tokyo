# 入出力制御関数

## dup

### プロトタイプ
```c
int dup(int oldfd);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルディスクリプタを複製し、最小の未使用ディスクリプタ番号を返します。

### パラメータ
- `oldfd`: 複製元のファイルディスクリプタ

### 戻り値
- 成功時: 新しいファイルディスクリプタ
- 失敗時: -1

### Minishellでの使用例

#### 標準入出力の保存
```c
// src/executor/redirect.c
int save_standard_fds(int *saved_stdin, int *saved_stdout)
{
    *saved_stdin = dup(STDIN_FILENO);
    if (*saved_stdin < 0)
        return (-1);
    
    *saved_stdout = dup(STDOUT_FILENO);
    if (*saved_stdout < 0)
    {
        close(*saved_stdin);
        return (-1);
    }
    
    return (0);
}
```

---

## dup2

### プロトタイプ
```c
int dup2(int oldfd, int newfd);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルディスクリプタを指定した番号に複製します。newfdが既に開いている場合は、自動的に閉じられます。

### パラメータ
- `oldfd`: 複製元のファイルディスクリプタ
- `newfd`: 複製先のファイルディスクリプタ番号

### 戻り値
- 成功時: newfd
- 失敗時: -1

### Minishellでの使用例

#### リダイレクション実装
```c
// src/executor/redirect.c
int apply_redirection(t_redir *redir)
{
    int fd;
    
    if (redir->type == REDIR_IN)
    {
        fd = open(redir->filename, O_RDONLY);
        if (fd < 0)
            return (-1);
        dup2(fd, STDIN_FILENO);
    }
    else if (redir->type == REDIR_OUT)
    {
        fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
            return (-1);
        dup2(fd, STDOUT_FILENO);
    }
    else if (redir->type == REDIR_APPEND)
    {
        fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
            return (-1);
        dup2(fd, STDOUT_FILENO);
    }
    
    close(fd);  // 複製後は元のFDを閉じる
    return (0);
}
```

#### パイプライン実装
```c
// src/executor/pipe_exec.c
void setup_pipe_left_child(int pipefd[2])
{
    // 標準出力をパイプの書き込み側に接続
    dup2(pipefd[1], STDOUT_FILENO);
    
    // 不要なFDを閉じる
    close(pipefd[0]);
    close(pipefd[1]);
}

void setup_pipe_right_child(int pipefd[2])
{
    // 標準入力をパイプの読み込み側に接続
    dup2(pipefd[0], STDIN_FILENO);
    
    // 不要なFDを閉じる
    close(pipefd[0]);
    close(pipefd[1]);
}
```

#### 標準入出力の復元
```c
// src/executor/redirect.c
void restore_standard_fds(int saved_stdin, int saved_stdout)
{
    if (saved_stdin >= 0)
    {
        dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
    }
    
    if (saved_stdout >= 0)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }
}
```

### 注意点
- **原子性**: dup2は原子的操作（close + dupの組み合わせより安全）
- **同じFDの場合**: oldfd == newfdの場合、何もしない
- **FDのクローズ**: 複製後は元のFDを閉じる

---

## pipe

### プロトタイプ
```c
int pipe(int pipefd[2]);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
プロセス間通信用のパイプを作成します。

### パラメータ
- `pipefd`: 2つのファイルディスクリプタを格納する配列
  - `pipefd[0]`: 読み込み側
  - `pipefd[1]`: 書き込み側

### 戻り値
- 成功時: 0
- 失敗時: -1

### Minishellでの使用例

#### 基本的なパイプライン
```c
// src/executor/pipe.c
int execute_pipeline(t_pipe *pipe_node, t_shell *shell)
{
    int     pipefd[2];
    pid_t   pid1, pid2;
    
    // パイプの作成
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    
    // 左側のコマンド（書き込み側）
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_node(pipe_node->left, shell);
        exit(shell->exit_status);
    }
    
    // 右側のコマンド（読み込み側）
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_node(pipe_node->right, shell);
        exit(shell->exit_status);
    }
    
    // 親プロセスはパイプを閉じる
    close(pipefd[0]);
    close(pipefd[1]);
    
    // 子プロセスを待機
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    
    return (0);
}
```

#### ヒアドキュメント用パイプ
```c
// src/executor/heredoc.c
int create_heredoc_pipe(const char *delimiter, t_shell *shell)
{
    int pipefd[2];
    
    if (pipe(pipefd) == -1)
        return (-1);
    
    pid_t pid = fork();
    if (pid == 0)
    {
        // 子プロセスでヒアドキュメント入力を処理
        close(pipefd[0]);
        
        char *line;
        while ((line = readline("> ")))
        {
            if (strcmp(line, delimiter) == 0)
            {
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
    
    return (pipefd[0]);  // 読み込み側を返す
}
```

### パイプの特性
- **バッファサイズ**: 通常64KB（システム依存）
- **ブロッキング**: バッファが満杯/空の場合ブロック
- **SIGPIPE**: 読み込み側が閉じられた状態で書き込むとシグナル発生

---

## isatty

### プロトタイプ
```c
int isatty(int fd);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルディスクリプタが端末デバイスを参照しているか確認します。

### パラメータ
- `fd`: チェックするファイルディスクリプタ

### 戻り値
- 端末の場合: 1
- 端末でない場合: 0

### Minishellでの使用例

#### インタラクティブモードの判定
```c
// src/main.c
int is_interactive_mode(void)
{
    return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}
```

#### ヒアドキュメント処理の分岐
```c
// src/executor/heredoc.c
int process_heredoc(const char *delimiter, t_shell *shell)
{
    if (isatty(STDIN_FILENO))
    {
        // インタラクティブモード：readlineとプロンプト表示
        return (process_heredoc_interactive(delimiter, shell));
    }
    else
    {
        // 非インタラクティブモード：get_next_line使用
        return (process_heredoc_non_interactive(delimiter, shell));
    }
}
```

#### プロンプト表示の制御
```c
// src/shell/shell_loop.c
void shell_loop(t_shell *shell)
{
    char *line;
    
    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            // 端末の場合：プロンプト表示
            line = readline("minishell$ ");
            if (line && *line)
                add_history(line);
        }
        else
        {
            // パイプやファイルからの入力
            line = get_next_line(STDIN_FILENO);
        }
        
        if (!line)
            break;
        
        process_line(line, shell);
        free(line);
    }
}
```

## 入出力制御のベストプラクティス

### 1. ファイルディスクリプタ管理

#### FDのライフサイクル
```c
// 1. 作成/オープン
int fd = open(filename, O_RDONLY);
// または
int pipefd[2];
pipe(pipefd);

// 2. 複製/リダイレクト
dup2(fd, STDIN_FILENO);

// 3. クローズ
close(fd);  // 不要になったら即座に閉じる
```

#### FDリークの防止
```c
void safe_pipe_execution(void)
{
    int pipefd[2];
    
    if (pipe(pipefd) == -1)
        return;
    
    pid_t pid = fork();
    if (pid == 0)
    {
        // 子プロセス：不要なFDを全て閉じる
        close(pipefd[0]);  // 読み込み側不要
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);  // 複製後は閉じる
        
        // 実行...
        exit(0);
    }
    
    // 親プロセス：両方閉じる
    close(pipefd[0]);
    close(pipefd[1]);
    
    waitpid(pid, NULL, 0);
}
```

### 2. リダイレクションパターン

#### 一時的なリダイレクション
```c
typedef struct s_fd_backup {
    int stdin_backup;
    int stdout_backup;
    int stderr_backup;
} t_fd_backup;

t_fd_backup *save_fds(void)
{
    t_fd_backup *backup = malloc(sizeof(t_fd_backup));
    
    backup->stdin_backup = dup(STDIN_FILENO);
    backup->stdout_backup = dup(STDOUT_FILENO);
    backup->stderr_backup = dup(STDERR_FILENO);
    
    return (backup);
}

void restore_fds(t_fd_backup *backup)
{
    dup2(backup->stdin_backup, STDIN_FILENO);
    dup2(backup->stdout_backup, STDOUT_FILENO);
    dup2(backup->stderr_backup, STDERR_FILENO);
    
    close(backup->stdin_backup);
    close(backup->stdout_backup);
    close(backup->stderr_backup);
    
    free(backup);
}
```

### 3. パイプラインの最適化

#### 複数パイプの管理
```c
// n個のコマンドに対してn-1個のパイプ
int **create_pipes(int n)
{
    int **pipes = malloc(sizeof(int *) * (n - 1));
    int i;
    
    for (i = 0; i < n - 1; i++)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(pipes[i]) == -1)
        {
            // エラー処理
            while (--i >= 0)
            {
                close(pipes[i][0]);
                close(pipes[i][1]);
                free(pipes[i]);
            }
            free(pipes);
            return (NULL);
        }
    }
    
    return (pipes);
}
```

### 4. エラー処理

```c
// dup2のエラーチェック
if (dup2(fd, STDOUT_FILENO) == -1)
{
    perror("dup2");
    close(fd);
    return (-1);
}

// pipeのエラーチェック
if (pipe(pipefd) == -1)
{
    perror("pipe");
    return (-1);
}
```

### 5. デバッグテクニック

```c
// FDの状態確認
void debug_fd_status(int fd)
{
    if (fcntl(fd, F_GETFD) == -1)
        printf("FD %d: closed\n", fd);
    else
        printf("FD %d: open\n", fd);
}

// 開いているFDの一覧
void list_open_fds(void)
{
    int fd;
    
    for (fd = 0; fd < 256; fd++)
    {
        if (fcntl(fd, F_GETFD) != -1)
            printf("FD %d is open\n", fd);
    }
}
```