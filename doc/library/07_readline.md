# Readline関数

## readline

### プロトタイプ
```c
char *readline(const char *prompt);
```

### ヘッダファイル
```c
#include <readline/readline.h>
```

### 説明
プロンプトを表示し、ユーザーから一行の入力を読み取ります。

### パラメータ
- `prompt`: 表示するプロンプト文字列

### 戻り値
- 成功時: 入力された文字列（mallocで確保）
- EOF時: NULL

### Minishellでの使用例

#### メインループでの使用
```c
// src/shell/shell_loop.c
void shell_loop(t_shell *shell)
{
    char *line;
    
    while (1)
    {
        // プロンプト表示と入力取得
        line = readline("minishell$ ");
        
        // Ctrl+D (EOF) の処理
        if (!line)
        {
            ft_putstr_fd("exit\n", STDERR_FILENO);
            break;
        }
        
        // 空行のスキップ
        if (!*line)
        {
            free(line);
            continue;
        }
        
        // 履歴に追加
        add_history(line);
        
        // コマンド処理
        process_line(line, shell);
        
        // メモリ解放（重要！）
        free(line);
    }
}
```

#### ヒアドキュメントでの使用
```c
// src/executor/heredoc.c
int read_heredoc_interactive(const char *delimiter, int write_fd)
{
    char *line;
    
    while (1)
    {
        // ヒアドキュメント用のプロンプト
        line = readline("> ");
        
        // Ctrl+D の処理
        if (!line)
        {
            ft_putstr_fd("\n", STDERR_FILENO);
            break;
        }
        
        // デリミタのチェック
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        
        // パイプへ書き込み
        write(write_fd, line, strlen(line));
        write(write_fd, "\n", 1);
        
        free(line);
    }
    
    return (0);
}
```

### 注意点
- **メモリ管理**: 返された文字列は必ずfreeする
- **メモリリーク**: readline内部のリークは42の仕様上許容
- **シグナル処理**: readlineはシグナルで中断される可能性がある

---

## add_history

### プロトタイプ
```c
void add_history(const char *line);
```

### ヘッダファイル
```c
#include <readline/history.h>
```

### 説明
入力された行を履歴リストに追加します。

### パラメータ
- `line`: 履歴に追加する文字列

### 戻り値
- なし

### Minishellでの使用例

```c
// src/shell/shell_loop.c
void process_input(t_shell *shell)
{
    char *line;
    
    line = readline("minishell$ ");
    if (!line)
        return;
    
    // 空行は履歴に追加しない
    if (*line)
    {
        add_history(line);
        process_line(line, shell);
    }
    
    free(line);
}
```

### 履歴管理のベストプラクティス
```c
// 重複を避ける
void add_to_history_unique(const char *line)
{
    HIST_ENTRY *last;
    
    // 最後の履歴エントリを取得
    using_history();
    last = previous_history();
    
    // 前回と同じコマンドは追加しない
    if (!last || strcmp(last->line, line) != 0)
        add_history(line);
}
```

---

## rl_clear_history

### プロトタイプ
```c
void rl_clear_history(void);
```

### ヘッダファイル
```c
#include <readline/history.h>
```

### 説明
履歴リストを全てクリアします。

### Minishellでの使用例

```c
// src/utils/cleanup.c
void cleanup_shell(t_shell *shell)
{
    // その他のクリーンアップ...
    
    // 履歴のクリア
    rl_clear_history();
    
    // メモリ解放...
}
```

---

## rl_on_new_line

### プロトタイプ
```c
int rl_on_new_line(void);
```

### ヘッダファイル
```c
#include <readline/readline.h>
```

### 説明
新しい行に移動したことをreadlineに通知します。主にシグナルハンドラで使用。

### 戻り値
- 常に0

### Minishellでの使用例

```c
// src/signal/signal_handler.c
void signal_handler_interactive(int signum)
{
    if (signum == SIGINT)
    {
        // 改行を出力
        write(STDERR_FILENO, "\n", 1);
        
        // readlineに新しい行を通知
        rl_on_new_line();
        
        // 現在の入力をクリア
        rl_replace_line("", 0);
        
        // プロンプトを再表示
        rl_redisplay();
    }
}
```

---

## rl_replace_line

### プロトタイプ
```c
void rl_replace_line(const char *text, int clear_undo);
```

### ヘッダファイル
```c
#include <readline/readline.h>
```

### 説明
現在の入力行を指定したテキストで置き換えます。

### パラメータ
- `text`: 新しいテキスト
- `clear_undo`: アンドゥ履歴をクリアするか（通常は0）

### Minishellでの使用例

```c
// src/signal/signal_handler.c
void handle_sigint(void)
{
    // 現在の入力をクリア
    rl_replace_line("", 0);
    
    // カーソルを行頭に
    rl_point = 0;
    
    // 再表示
    rl_redisplay();
}
```

---

## rl_redisplay

### プロトタイプ
```c
int rl_redisplay(void);
```

### ヘッダファイル
```c
#include <readline/readline.h>
```

### 説明
現在のプロンプトと入力行を再表示します。

### 戻り値
- 常に0

### Minishellでの使用例

```c
// src/signal/signal_handler.c
void signal_handler_interactive(int signum)
{
    g_signal_received = signum;
    
    if (signum == SIGINT)
    {
        // 改行
        write(STDERR_FILENO, "\n", 1);
        
        // readlineの状態をリセット
        rl_on_new_line();
        rl_replace_line("", 0);
        
        // プロンプトと入力行を再表示
        rl_redisplay();
    }
}
```

## Readlineの設定とカスタマイズ

### グローバル変数

```c
// src/main.c
void setup_readline(void)
{
    // Ctrl+Cなどのシグナルをreadlineに処理させない
    rl_catch_signals = 0;
    
    // Ctrl+Zなどの停止シグナルも処理しない
    rl_catch_sigwinch = 0;
    
    // プロンプトの設定
    rl_prompt = "minishell$ ";
    
    // 履歴の最大サイズ
    using_history();
    stifle_history(1000);
}
```

### カスタムコンプリーション（オプション）

```c
// タブ補完のカスタマイズ例
char **minishell_completion(const char *text, int start, int end)
{
    char **matches = NULL;
    
    // コマンドの最初の単語の場合
    if (start == 0)
    {
        // コマンド名の補完
        matches = rl_completion_matches(text, command_generator);
    }
    else
    {
        // ファイル名の補完（デフォルト）
        matches = rl_completion_matches(text, rl_filename_completion_function);
    }
    
    return (matches);
}

// 初期化時に設定
void init_completion(void)
{
    rl_attempted_completion_function = minishell_completion;
}
```

## Readlineとシグナル処理の統合

### シグナルハンドラでの注意点

```c
// src/signal/signal_handler.c

// シグナルセーフな関数のみ使用
void signal_handler_safe(int signum)
{
    // グローバル変数への書き込みのみ
    g_signal_received = signum;
}

// メインループでの処理
void check_signal_in_main_loop(t_shell *shell)
{
    if (g_signal_received == SIGINT)
    {
        // ここでreadline関数を呼べる
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        
        shell->exit_status = 130;
        g_signal_received = 0;
    }
}
```

## メモリリークについて

### Readlineのメモリリーク

```c
// valgrindでの確認時
// readlineは内部でメモリを確保し、一部は解放されない
// これは42の仕様上許容される

// suppressionファイルの例
{
   readline_leak
   Memcheck:Leak
   ...
   fun:readline
}
```

### 自前のメモリ管理

```c
void proper_cleanup(void)
{
    char *line;
    
    line = readline("$ ");
    if (line)
    {
        // 使用後は必ず解放
        process_line(line);
        free(line);  // これは必須！
    }
}
```

## トラブルシューティング

### 1. プロンプトが表示されない

```c
// 端末チェック
if (!isatty(STDIN_FILENO))
{
    // パイプやファイルからの入力時はreadlineを使わない
    use_get_next_line_instead();
}
```

### 2. Ctrl+Cで複数のプロンプトが表示される

```c
// フラグで二重処理を防ぐ
static int handling_signal = 0;

void signal_handler(int signum)
{
    if (handling_signal)
        return;
    
    handling_signal = 1;
    // シグナル処理
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    handling_signal = 0;
}
```

### 3. 履歴が保存されない

```c
// 履歴ファイルの保存と読み込み
void save_history_to_file(void)
{
    char *home = getenv("HOME");
    char history_file[PATH_MAX];
    
    if (home)
    {
        snprintf(history_file, PATH_MAX, "%s/.minishell_history", home);
        write_history(history_file);
    }
}

void load_history_from_file(void)
{
    char *home = getenv("HOME");
    char history_file[PATH_MAX];
    
    if (home)
    {
        snprintf(history_file, PATH_MAX, "%s/.minishell_history", home);
        read_history(history_file);
    }
}
```