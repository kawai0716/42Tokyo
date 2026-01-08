# エラー処理関数

## perror

### プロトタイプ
```c
void perror(const char *s);
```

### ヘッダファイル
```c
#include <stdio.h>
```

### 説明
システムエラーメッセージを標準エラー出力に表示します。errnoの値に基づいてエラーメッセージを生成します。

### パラメータ
- `s`: エラーメッセージの前に表示する文字列（NULLも可）

### 戻り値
- なし

### Minishellでの使用例

#### ファイルオープンエラー
```c
// src/executor/redirect.c
int open_input_file(const char *filename)
{
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        // "minishell: filename: エラーメッセージ" の形式で出力
        perror(filename);
        return (-1);
    }
    
    return (fd);
}
```

#### fork失敗時のエラー処理
```c
// src/executor/execute.c
pid_t create_child_process(void)
{
    pid_t pid;
    
    pid = fork();
    if (pid == -1)
    {
        // "minishell: fork: Resource temporarily unavailable" など
        perror("minishell: fork");
        return (-1);
    }
    
    return (pid);
}
```

#### execve失敗時のエラー処理
```c
// src/executor/cmd_exec.c
void execute_command(char *cmd, char **argv, char **envp)
{
    execve(cmd, argv, envp);
    
    // execveが戻ってきた場合は必ずエラー
    perror(cmd);
    
    // errnoに応じた終了コード
    if (errno == ENOENT)
        exit(127);  // Command not found
    else if (errno == EACCES)
        exit(126);  // Permission denied
    else
        exit(1);    // その他のエラー
}
```

### errno値と対応するエラーメッセージ

| errno | メッセージ | 状況 |
|-------|-----------|------|
| ENOENT | No such file or directory | ファイルが存在しない |
| EACCES | Permission denied | アクセス権限なし |
| ENOTDIR | Not a directory | ディレクトリではない |
| EISDIR | Is a directory | ディレクトリをファイルとして開こうとした |
| EMFILE | Too many open files | プロセスのFD上限 |
| ENOMEM | Out of memory | メモリ不足 |
| EAGAIN | Resource temporarily unavailable | リソース一時的に利用不可 |

## エラー処理のパターン

### 1. カスタムエラーメッセージ

```c
// src/error/error.c
void print_error(const char *cmd, const char *arg, const char *msg)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    
    if (cmd)
    {
        ft_putstr_fd(cmd, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    
    if (arg)
    {
        ft_putstr_fd(arg, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    
    ft_putstr_fd(msg, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

// 使用例
print_error("cd", "/invalid/path", "No such file or directory");
// 出力: minishell: cd: /invalid/path: No such file or directory
```

### 2. 構文エラーの処理

```c
// src/error/error_handler.c
void print_syntax_error(const char *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 
                  STDERR_FILENO);
    ft_putstr_fd(token, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
}

// 使用例：パイプの後に何もない場合
if (token->type == TOKEN_PIPE && !token->next)
{
    print_syntax_error("|");
    return (NULL);
}
```

### 3. エラーコードの管理

```c
// src/error/error_utils.c

// エラーコード定義
#define ERROR_SUCCESS           0
#define ERROR_GENERAL           1
#define ERROR_BUILTIN_USAGE     2
#define ERROR_EXEC_NOT_FOUND    127
#define ERROR_EXEC_NO_PERM      126
#define ERROR_SIGNAL_BASE       128

// エラーコードを返す関数
int get_error_code(int error_type)
{
    switch (error_type)
    {
        case ENOENT:
            return (ERROR_EXEC_NOT_FOUND);
        case EACCES:
            return (ERROR_EXEC_NO_PERM);
        default:
            return (ERROR_GENERAL);
    }
}
```

### 4. ビルトインコマンドのエラー処理

```c
// src/builtin/builtin_cd.c
int builtin_cd_error(const char *path, int error_code)
{
    ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
    
    if (path)
    {
        ft_putstr_fd(path, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
    }
    
    switch (error_code)
    {
        case ENOENT:
            ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
            break;
        case ENOTDIR:
            ft_putstr_fd("Not a directory\n", STDERR_FILENO);
            break;
        case EACCES:
            ft_putstr_fd("Permission denied\n", STDERR_FILENO);
            break;
        default:
            perror("cd");
    }
    
    return (1);
}
```

### 5. パイプラインエラーの処理

```c
// src/executor/pipe_error.c
void handle_pipe_error(t_shell *shell)
{
    if (errno == EMFILE)
    {
        ft_putstr_fd("minishell: pipe: Too many open files\n", 
                      STDERR_FILENO);
    }
    else
    {
        perror("minishell: pipe");
    }
    
    shell->exit_status = 1;
}
```

### 6. メモリ割り当てエラー

```c
// src/utils/memory_error.c
void *safe_malloc(size_t size)
{
    void *ptr;
    
    ptr = malloc(size);
    if (!ptr)
    {
        ft_putstr_fd("minishell: malloc: Out of memory\n", 
                      STDERR_FILENO);
        exit(1);
    }
    
    return (ptr);
}
```

## エラー処理のベストプラクティス

### 1. 一貫したエラーフォーマット

```c
// bashと同じフォーマットを使用
// プログラム名: コマンド: 引数: エラーメッセージ

void format_error(const char *cmd, const char *arg)
{
    char buffer[256];
    
    snprintf(buffer, sizeof(buffer), 
             "minishell: %s: %s: %s",
             cmd, arg, strerror(errno));
    
    ft_putstr_fd(buffer, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}
```

### 2. エラーの伝播

```c
// エラーを上位層に伝播
int process_command(t_cmd *cmd, t_shell *shell)
{
    int result;
    
    result = validate_command(cmd);
    if (result < 0)
        return (result);  // エラーを伝播
    
    result = execute_command(cmd, shell);
    if (result < 0)
        return (result);  // エラーを伝播
    
    return (0);
}
```

### 3. クリーンアップを含むエラー処理

```c
// リソースの適切な解放
int process_with_cleanup(void)
{
    char *buffer = NULL;
    int fd = -1;
    int result = -1;
    
    buffer = malloc(1024);
    if (!buffer)
        goto cleanup;
    
    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("file.txt");
        goto cleanup;
    }
    
    // 処理...
    result = 0;
    
cleanup:
    if (buffer)
        free(buffer);
    if (fd >= 0)
        close(fd);
    
    return (result);
}
```

### 4. デバッグモード

```c
// デバッグ用の詳細エラー出力
#ifdef DEBUG
    #define DEBUG_ERROR(fmt, ...) \
        fprintf(stderr, "[%s:%d] " fmt "\n", \
                __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_ERROR(fmt, ...)
#endif

// 使用例
int open_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    
    if (fd < 0)
    {
        DEBUG_ERROR("Failed to open %s: %s", 
                    filename, strerror(errno));
        perror(filename);
        return (-1);
    }
    
    return (fd);
}
```

## エラー処理チェックリスト

### システムコール
- [ ] fork() のエラーチェック
- [ ] pipe() のエラーチェック
- [ ] dup2() のエラーチェック
- [ ] open() のエラーチェック
- [ ] execve() のエラー処理と適切な終了コード

### メモリ管理
- [ ] malloc() のNULLチェック
- [ ] エラー時のメモリ解放

### ファイル操作
- [ ] ファイルオープンのエラー処理
- [ ] ディレクトリ操作のエラー処理
- [ ] エラー時のFDクローズ

### ユーザー入力
- [ ] 構文エラーの検出と報告
- [ ] 不正な引数の処理
- [ ] 空入力の処理

### エラーメッセージ
- [ ] bashと一貫性のあるフォーマット
- [ ] 適切な終了ステータスの設定
- [ ] stderr への出力