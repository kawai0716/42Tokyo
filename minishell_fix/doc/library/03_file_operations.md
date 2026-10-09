# ファイル操作関数

## open

### プロトタイプ
```c
int open(const char *pathname, int flags, mode_t mode);
```

### ヘッダファイル
```c
#include <fcntl.h>
```

### 説明
ファイルを開き、ファイルディスクリプタを返します。

### パラメータ
- `pathname`: 開くファイルのパス
- `flags`: オープンモード（O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC, O_APPEND等）
- `mode`: ファイル作成時のパーミッション（O_CREAT使用時のみ）

### 戻り値
- 成功時: ファイルディスクリプタ（非負の整数）
- 失敗時: -1（errnoが設定される）

### Minishellでの使用例

#### 入力リダイレクション
```c
// src/executor/redirect.c
int setup_input_redirection(char *filename)
{
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror(filename);
        return (-1);
    }
    
    if (dup2(fd, STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    
    close(fd);  // 複製後は元のFDを閉じる
    return (0);
}
```

#### 出力リダイレクション
```c
// src/executor/redirect.c
int setup_output_redirection(char *filename, int append)
{
    int fd;
    int flags;
    
    if (append)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    
    fd = open(filename, flags, 0644);
    if (fd < 0)
    {
        perror(filename);
        return (-1);
    }
    
    if (dup2(fd, STDOUT_FILENO) < 0)
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    
    close(fd);
    return (0);
}
```

### フラグの組み合わせ
| フラグ | 説明 | 使用場面 |
|--------|------|----------|
| O_RDONLY | 読み込み専用 | `< file` |
| O_WRONLY \| O_CREAT \| O_TRUNC | 書き込み、作成、切り詰め | `> file` |
| O_WRONLY \| O_CREAT \| O_APPEND | 書き込み、作成、追記 | `>> file` |

---

## close

### プロトタイプ
```c
int close(int fd);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルディスクリプタを閉じます。

### パラメータ
- `fd`: 閉じるファイルディスクリプタ

### 戻り値
- 成功時: 0
- 失敗時: -1

### Minishellでの使用例

#### パイプのFD管理
```c
// src/executor/pipe.c
void close_pipe_fds(int pipefd[2])
{
    close(pipefd[0]);
    close(pipefd[1]);
}

void setup_pipe_child(int pipefd[2], int is_left)
{
    if (is_left)
    {
        close(pipefd[0]);  // 読み込み側を閉じる
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);  // 複製後は閉じる
    }
    else
    {
        close(pipefd[1]);  // 書き込み側を閉じる
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);  // 複製後は閉じる
    }
}
```

### 注意点
- **FDリーク防止**: 不要になったFDは即座に閉じる
- **fork後の処理**: 子プロセスで不要なFDを閉じる
- **dup2後の処理**: 複製元のFDは閉じる

---

## read

### プロトタイプ
```c
ssize_t read(int fd, void *buf, size_t count);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルディスクリプタからデータを読み込みます。

### パラメータ
- `fd`: 読み込み元のファイルディスクリプタ
- `buf`: データを格納するバッファ
- `count`: 読み込む最大バイト数

### 戻り値
- 成功時: 読み込んだバイト数
- EOF時: 0
- エラー時: -1

### Minishellでの使用例

#### get_next_line実装
```c
// src/utils/get_next_line.c
static int read_buffer(int fd, char **buffer, int *buffer_size)
{
    char    *tmp;
    int     bytes_read;
    
    tmp = malloc(BUFFER_SIZE + 1);
    if (!tmp)
        return (-1);
    
    bytes_read = read(fd, tmp, BUFFER_SIZE);
    if (bytes_read <= 0)
    {
        free(tmp);
        return (bytes_read);
    }
    
    tmp[bytes_read] = '\0';
    *buffer = join_strings(*buffer, tmp);
    *buffer_size += bytes_read;
    free(tmp);
    
    return (bytes_read);
}
```

#### ヒアドキュメント処理（非対話モード）
```c
// src/executor/heredoc.c
int read_heredoc_stdin(const char *delimiter)
{
    char    buffer[1024];
    ssize_t bytes_read;
    
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        // デリミタのチェックと処理
        if (check_delimiter(buffer, delimiter))
            break;
        // パイプへの書き込み
        write(pipefd[1], buffer, bytes_read);
    }
    
    return (0);
}
```

---

## write

### プロトタイプ
```c
ssize_t write(int fd, const void *buf, size_t count);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルディスクリプタにデータを書き込みます。

### パラメータ
- `fd`: 書き込み先のファイルディスクリプタ
- `buf`: 書き込むデータ
- `count`: 書き込むバイト数

### 戻り値
- 成功時: 書き込んだバイト数
- エラー時: -1

### Minishellでの使用例

#### エラーメッセージ出力
```c
// src/error/error.c
void print_error(const char *msg)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}
```

#### シグナルハンドラ内での使用
```c
// src/signal/signal_handler.c
void signal_handler_interactive(int signum)
{
    if (signum == SIGINT)
    {
        // シグナルハンドラ内ではwriteのみ使用可能
        write(STDERR_FILENO, "\n", 1);
        // readlineの処理...
    }
}
```

### 注意点
- **シグナルセーフ**: writeはシグナルハンドラ内で使用可能
- **部分書き込み**: 戻り値のチェックが重要
- **SIGPIPE**: パイプが閉じられた場合の処理

---

## access

### プロトタイプ
```c
int access(const char *pathname, int mode);
```

### ヘッダファイル
```c
#include <unistd.h>
```

### 説明
ファイルのアクセス権限を確認します。

### パラメータ
- `pathname`: チェックするファイルのパス
- `mode`: チェックするアクセス権（F_OK, R_OK, W_OK, X_OK）

### 戻り値
- アクセス可能: 0
- アクセス不可: -1

### Minishellでの使用例

#### コマンドの実行可能性チェック
```c
// src/executor/cmd_path.c
char *find_executable(const char *cmd, char **paths)
{
    char    *full_path;
    int     i;
    
    // 絶対パスまたは相対パスの場合
    if (strchr(cmd, '/'))
    {
        if (access(cmd, F_OK) == 0)
        {
            if (access(cmd, X_OK) == 0)
                return (strdup(cmd));
            else
            {
                // ファイルは存在するが実行権限なし
                errno = EACCES;
                return (NULL);
            }
        }
        return (NULL);
    }
    
    // PATHから検索
    i = 0;
    while (paths[i])
    {
        full_path = join_path(paths[i], cmd);
        if (access(full_path, X_OK) == 0)
            return (full_path);
        free(full_path);
        i++;
    }
    
    return (NULL);
}
```

### アクセスモード
| モード | 説明 |
|--------|------|
| F_OK | ファイルの存在確認 |
| R_OK | 読み込み権限確認 |
| W_OK | 書き込み権限確認 |
| X_OK | 実行権限確認 |

---

## stat

### プロトタイプ
```c
int stat(const char *pathname, struct stat *statbuf);
```

### ヘッダファイル
```c
#include <sys/stat.h>
```

### 説明
ファイルの詳細情報を取得します。

### パラメータ
- `pathname`: 情報を取得するファイルのパス
- `statbuf`: ファイル情報を格納する構造体へのポインタ

### 戻り値
- 成功時: 0
- 失敗時: -1

### Minishellでの使用例

#### ディレクトリ判定
```c
// src/builtin/builtin_cd.c
int is_directory(const char *path)
{
    struct stat statbuf;
    
    if (stat(path, &statbuf) == -1)
        return (0);
    
    return (S_ISDIR(statbuf.st_mode));
}
```

#### ファイルタイプの判定
```c
// src/executor/cmd_exec.c
int check_file_type(const char *path)
{
    struct stat statbuf;
    
    if (stat(path, &statbuf) == -1)
    {
        // ファイルが存在しない
        return (FILE_NOT_FOUND);
    }
    
    if (S_ISDIR(statbuf.st_mode))
    {
        // ディレクトリ
        return (IS_DIRECTORY);
    }
    else if (S_ISREG(statbuf.st_mode))
    {
        // 通常ファイル
        if (statbuf.st_mode & S_IXUSR)
            return (IS_EXECUTABLE);
        else
            return (NOT_EXECUTABLE);
    }
    
    return (OTHER_TYPE);
}
```

### ファイルタイプマクロ
| マクロ | 説明 |
|--------|------|
| S_ISREG(m) | 通常ファイル |
| S_ISDIR(m) | ディレクトリ |
| S_ISLNK(m) | シンボリックリンク |
| S_ISFIFO(m) | FIFO（名前付きパイプ） |

## ファイル操作のベストプラクティス

### 1. エラー処理
```c
int fd = open(filename, O_RDONLY);
if (fd < 0)
{
    // エラーの種類に応じた処理
    if (errno == ENOENT)
        print_error("No such file or directory");
    else if (errno == EACCES)
        print_error("Permission denied");
    else
        perror(filename);
    return (-1);
}
```

### 2. FDのクリーンアップ
```c
// RAII風の処理
int process_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (-1);
    
    // ファイル処理
    int result = do_something(fd);
    
    // 必ずクローズ
    close(fd);
    return (result);
}
```

### 3. リダイレクションの復元
```c
// 標準入出力の保存と復元
int saved_stdin = dup(STDIN_FILENO);
int saved_stdout = dup(STDOUT_FILENO);

// リダイレクション実行
setup_redirections();
execute_command();

// 復元
dup2(saved_stdin, STDIN_FILENO);
dup2(saved_stdout, STDOUT_FILENO);
close(saved_stdin);
close(saved_stdout);
```