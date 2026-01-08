# EOF（Ctrl+D）の処理

## 1. Ctrl+Dとは

Ctrl+Dは**シグナルではなく**、端末からEOF（End Of File）を送信する特殊な入力です。

### シグナルとの違い

| 入力 | 種類 | 処理方法 | 関数の戻り値 |
|------|------|----------|-------------|
| Ctrl+C | シグナル（SIGINT） | シグナルハンドラで処理 | - |
| Ctrl+\ | シグナル（SIGQUIT） | シグナルハンドラで処理 | - |
| Ctrl+D | EOF | 関数の戻り値で検出 | NULL or 0 |

## 2. readline()でのCtrl+D処理

### 基本的な処理

```c
// src/shell/shell_loop.c
void shell_loop(t_shell *shell)
{
    char *line;
    
    while (1)
    {
        line = readline("minishell$ ");
        
        // Ctrl+D が押された場合、readline()はNULLを返す
        if (!line)
        {
            // "exit"を表示してシェルを終了
            ft_putstr_fd("exit\n", STDERR_FILENO);
            break;  // または exit(shell->exit_status);
        }
        
        // 通常の処理
        if (*line)
        {
            add_history(line);
            process_line(line, shell);
        }
        
        free(line);
    }
}
```

### 入力がある状態でのCtrl+D

```c
// readline()の動作
// 1. 空行でCtrl+D → NULLを返す（シェル終了）
// 2. 文字入力後にCtrl+D → 入力を確定（改行と同じ）

// 例：
// minishell$ echo hello[Ctrl+D]
// → "echo hello"が入力として処理される（改行と同じ）

// minishell$ [Ctrl+D]
// → NULLが返され、シェルが終了
```

## 3. get_next_line()でのCtrl+D処理

### 非対話モードでの処理

```c
// src/utils/get_next_line.c
char *get_next_line_minishell(t_gnl_data *data)
{
    ssize_t bytes_read;
    char    buffer[BUFFER_SIZE];
    
    while (1)
    {
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        
        // EOF（Ctrl+Dまたはファイル終端）
        if (bytes_read == 0)
        {
            // バッファに残りがあれば返す
            if (data->leftover && *data->leftover)
                return (extract_line(data));
            
            // 完全に終了
            return (NULL);
        }
        
        // エラー
        if (bytes_read < 0)
            return (NULL);
        
        // 通常の処理
        buffer[bytes_read] = '\0';
        append_to_buffer(data, buffer);
        
        if (strchr(buffer, '\n'))
            return (extract_line(data));
    }
}
```

## 4. ヒアドキュメントでのCtrl+D処理

### インタラクティブモードのヒアドキュメント

```c
// src/executor/heredoc.c
int read_heredoc_interactive(const char *delimiter, int write_fd, t_shell *shell)
{
    char *line;
    pid_t pid;
    
    pid = fork();
    if (pid == 0)
    {
        // 子プロセスでヒアドキュメントを処理
        signal(SIGINT, SIG_DFL);  // Ctrl+Cで中断可能
        
        while (1)
        {
            line = readline("> ");
            
            // Ctrl+D が押された場合
            if (!line)
            {
                // bash互換：警告メッセージを表示
                ft_putstr_fd("minishell: warning: here-document ", 2);
                ft_putstr_fd("delimited by end-of-file (wanted `", 2);
                ft_putstr_fd(delimiter, 2);
                ft_putstr_fd("')\n", 2);
                break;
            }
            
            // デリミタチェック
            if (strcmp(line, delimiter) == 0)
            {
                free(line);
                break;
            }
            
            // パイプに書き込み
            write(write_fd, line, strlen(line));
            write(write_fd, "\n", 1);
            free(line);
        }
        
        close(write_fd);
        exit(0);
    }
    
    // 親プロセス
    close(write_fd);
    
    int status;
    waitpid(pid, &status, 0);
    
    return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
}
```

### 非インタラクティブモードのヒアドキュメント

```c
// src/executor/heredoc_utils.c
int read_heredoc_non_interactive(const char *delimiter, int write_fd)
{
    char    *line;
    
    while ((line = get_next_line(STDIN_FILENO)))
    {
        // デリミタチェック（改行を除去）
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // 改行を戻して書き込み
        write(write_fd, line, strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
    
    // EOFに達した場合（Ctrl+Dまたはファイル終端）
    if (!line)
    {
        // 警告は表示しない（非インタラクティブ）
    }
    
    return (0);
}
```

## 5. パイプからの入力でのEOF

### パイプ経由での実行

```bash
# コマンドをパイプで送信
echo "echo hello" | ./minishell
# → "hello"を出力してminishellは終了

# 複数コマンド
echo -e "echo hello\necho world" | ./minishell
# → "hello"と"world"を出力して終了

# ファイルから読み込み
./minishell < commands.txt
# → ファイルの全コマンドを実行して終了
```

### 実装例

```c
// src/main.c
int main(int argc, char **argv, char **envp)
{
    t_shell *shell;
    
    shell = init_shell(envp);
    
    // インタラクティブモードの判定
    if (isatty(STDIN_FILENO))
    {
        // 端末からの入力：プロンプト表示
        interactive_loop(shell);
    }
    else
    {
        // パイプ/ファイルからの入力：プロンプトなし
        non_interactive_loop(shell);
    }
    
    cleanup_shell(shell);
    return (shell->exit_status);
}

void non_interactive_loop(t_shell *shell)
{
    char *line;
    
    // get_next_lineを使用（readlineは使わない）
    while ((line = get_next_line(STDIN_FILENO)))
    {
        process_line(line, shell);
        free(line);
    }
    
    // EOFに達したら自動的に終了
}
```

## 6. EOFと終了ステータス

### 正常終了時の処理

```c
// src/shell/shell_loop.c
void handle_eof(t_shell *shell)
{
    // bashと同じ"exit"メッセージ
    if (isatty(STDIN_FILENO))
    {
        ft_putstr_fd("exit\n", STDERR_FILENO);
    }
    
    // 終了ステータスは最後のコマンドのものを保持
    exit(shell->exit_status);
}
```

## 7. エッジケースの処理

### 1. 連続したCtrl+D

```c
// readline()は各呼び出しで独立して処理
// 連続したCtrl+Dは最初の1回で終了
```

### 2. バックグラウンド実行時

```bash
# バックグラウンドで実行
./minishell &
# → TTYからの読み込みで停止（SIGTTIN）
```

### 3. nohupでの実行

```bash
nohup ./minishell < /dev/null &
# → 即座に終了（/dev/nullからEOF）
```

## 8. テストケース

### インタラクティブモードのテスト

```bash
# テスト1: 空行でCtrl+D
$ ./minishell
minishell$ [Ctrl+D]
exit
$

# テスト2: コマンド入力後にCtrl+D
$ ./minishell
minishell$ echo hello[Ctrl+D]
hello
minishell$ 

# テスト3: ヒアドキュメント中のCtrl+D
$ ./minishell
minishell$ cat << EOF
> hello
> [Ctrl+D]
minishell: warning: here-document delimited by end-of-file (wanted `EOF')
hello
minishell$
```

### 非インタラクティブモードのテスト

```bash
# テスト1: パイプ経由
$ echo "echo test" | ./minishell
test
$

# テスト2: ファイルリダイレクション
$ echo "pwd" > cmd.txt
$ ./minishell < cmd.txt
/home/user/minishell
$

# テスト3: 空の入力
$ echo -n "" | ./minishell
$ echo $?
0  # 前回の終了ステータスを保持
```

## 9. bashとの互換性

### bash の動作

```bash
# bash でのCtrl+D
$ bash
bash-5.0$ [Ctrl+D]
exit
$

# 入力がある状態
bash-5.0$ echo test[Ctrl+D]
test
bash-5.0$

# ヒアドキュメント
bash-5.0$ cat << EOF
> hello
> [Ctrl+D]
bash: warning: here-document at line 1 delimited by end-of-file (wanted `EOF')
hello
bash-5.0$
```

### minishellでの実装指針

1. **"exit"メッセージ**: インタラクティブモードでのみ表示
2. **終了ステータス**: 最後に実行したコマンドのステータスを保持
3. **ヒアドキュメント警告**: bashと同じフォーマットで表示
4. **非インタラクティブ**: メッセージなしで静かに終了

## 10. 実装上の注意点

### メモリ管理

```c
// readline()がNULLを返した場合もクリーンアップ
if (!line)
{
    // 履歴のクリア
    rl_clear_history();
    
    // その他のクリーンアップ
    cleanup_shell(shell);
    
    ft_putstr_fd("exit\n", STDERR_FILENO);
    exit(shell->exit_status);
}
```

### シグナルとの相互作用

```c
// Ctrl+CとCtrl+Dの違いを理解
// Ctrl+C: シグナルハンドラが呼ばれる
// Ctrl+D: readline()がNULLを返す

// 両方を適切に処理
if (g_signal_received == SIGINT)
{
    // Ctrl+Cの処理
    shell->exit_status = 130;
    g_signal_received = 0;
}
else if (!line)
{
    // Ctrl+Dの処理
    handle_eof(shell);
}
```