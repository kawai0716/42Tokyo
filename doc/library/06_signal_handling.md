# シグナル処理関数

## signal

### プロトタイプ
```c
void (*signal(int signum, void (*handler)(int)))(int);
```

### ヘッダファイル
```c
#include <signal.h>
```

### 説明
シグナルハンドラを設定します（簡易版、sigaction()の使用を推奨）。

### パラメータ
- `signum`: シグナル番号（SIGINT、SIGQUIT等）
- `handler`: シグナルハンドラ関数またはSIG_DFL、SIG_IGN

### 戻り値
- 成功時: 以前のシグナルハンドラ
- 失敗時: SIG_ERR

### Minishellでの使用例

#### 子プロセスでのシグナルリセット
```c
// src/executor/cmd_exec.c
void reset_signals_in_child(void)
{
    // デフォルトのシグナルハンドラに戻す
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void execute_child_process(char *cmd, char **argv, char **envp)
{
    // 子プロセスでシグナルをリセット
    reset_signals_in_child();
    
    // コマンド実行
    execve(cmd, argv, envp);
    
    // execve失敗時
    perror(cmd);
    exit(127);
}
```

#### SIG_IGNの使用
```c
// src/signal/signal.c
void ignore_signals(void)
{
    // SIGQUITを無視
    signal(SIGQUIT, SIG_IGN);
}
```

### 注意点
- **非推奨**: POSIXではsigaction()の使用を推奨
- **移植性**: システムによって動作が異なる
- **制限**: より詳細な制御ができない

---

## sigaction

### プロトタイプ
```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```

### ヘッダファイル
```c
#include <signal.h>
```

### 説明
シグナルハンドラを詳細に設定します。

### パラメータ
- `signum`: シグナル番号
- `act`: 新しいシグナルアクション（NULLで現在の設定を取得）
- `oldact`: 以前のシグナルアクション（NULLも可）

### sigaction構造体
```c
struct sigaction {
    void     (*sa_handler)(int);       // シグナルハンドラ
    void     (*sa_sigaction)(int, siginfo_t *, void *); // 拡張ハンドラ
    sigset_t sa_mask;                  // ハンドラ実行中にブロックするシグナル
    int      sa_flags;                 // フラグ
    void     (*sa_restorer)(void);     // 廃止予定
};
```

### 戻り値
- 成功時: 0
- 失敗時: -1

### Minishellでの使用例

#### インタラクティブモードのシグナル設定
```c
// src/signal/signal.c
void init_signal(void)
{
    struct sigaction sa;
    
    // SIGINT（Ctrl+C）の設定
    sa.sa_handler = signal_handler_interactive;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;  // システムコールを再開
    
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
    
    // SIGQUIT（Ctrl+\）を無視
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
}
```

#### 実行モードのシグナル設定
```c
// src/signal/signal.c
void set_execution_signal(void)
{
    struct sigaction sa;
    
    // 親プロセスはSIGINTを特別に処理
    sa.sa_handler = signal_handler_executing;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;  // SA_RESTARTなし
    
    sigaction(SIGINT, &sa, NULL);
    
    // SIGQUITは引き続き無視
    signal(SIGQUIT, SIG_IGN);
}
```

#### シグナルハンドラの実装
```c
// src/signal/signal_handler.c
void signal_handler_interactive(int signum)
{
    // グローバル変数に記録（シグナルセーフ）
    g_signal_received = signum;
    
    if (signum == SIGINT)
    {
        // 改行を出力（writeはシグナルセーフ）
        write(STDERR_FILENO, "\n", 1);
        
        // readlineの状態をリセット
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void signal_handler_executing(int signum)
{
    // 実行中は記録のみ
    g_signal_received = signum;
}
```

### sa_flagsの主要なフラグ
| フラグ | 説明 |
|--------|------|
| SA_RESTART | システムコールを自動的に再開 |
| SA_NOCLDSTOP | 子プロセスの停止時にSIGCHLDを送らない |
| SA_NOCLDWAIT | 子プロセスをゾンビにしない |
| SA_RESETHAND | ハンドラ実行後にSIG_DFLにリセット |

---

## sigemptyset

### プロトタイプ
```c
int sigemptyset(sigset_t *set);
```

### ヘッダファイル
```c
#include <signal.h>
```

### 説明
シグナルセットを空に初期化します。

### パラメータ
- `set`: 初期化するシグナルセット

### 戻り値
- 成功時: 0
- 失敗時: -1

### Minishellでの使用例

#### シグナルマスクの初期化
```c
// src/signal/signal.c
void setup_signal_handler(int signum, void (*handler)(int))
{
    struct sigaction sa;
    
    sa.sa_handler = handler;
    
    // シグナルマスクを空に初期化
    sigemptyset(&sa.sa_mask);
    
    // オプション：特定のシグナルをブロック
    // sigaddset(&sa.sa_mask, SIGTERM);
    
    sa.sa_flags = SA_RESTART;
    
    if (sigaction(signum, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(1);
    }
}
```

#### 複数シグナルのマスク設定
```c
// src/signal/signal_utils.c
void block_signals_during_critical_section(void)
{
    sigset_t mask;
    
    // 空のシグナルセットを作成
    sigemptyset(&mask);
    
    // ブロックしたいシグナルを追加
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTERM);
    
    // シグナルをブロック
    sigprocmask(SIG_BLOCK, &mask, NULL);
}

void unblock_signals(void)
{
    sigset_t mask;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTERM);
    
    // シグナルのブロックを解除
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
}
```

## シグナル処理のパターン

### 1. グローバル変数の使用

```c
// src/signal/signal_handler.c

// 唯一のグローバル変数（42の仕様）
volatile sig_atomic_t g_signal_received = 0;

// シグナルハンドラ（最小限の処理）
void minimal_signal_handler(int signum)
{
    g_signal_received = signum;
}

// メインループでの処理
void process_pending_signal(t_shell *shell)
{
    if (g_signal_received == SIGINT)
    {
        shell->exit_status = 130;  // 128 + SIGINT(2)
        g_signal_received = 0;
    }
    else if (g_signal_received == SIGQUIT)
    {
        shell->exit_status = 131;  // 128 + SIGQUIT(3)
        g_signal_received = 0;
    }
}
```

### 2. モード別シグナル処理

```c
// src/signal/signal_mode.c

typedef enum e_shell_mode {
    MODE_INTERACTIVE = 0,
    MODE_HEREDOC = 1,
    MODE_EXECUTING = 2
} t_shell_mode;

void set_signal_mode(t_shell_mode mode)
{
    struct sigaction sa;
    
    switch (mode)
    {
        case MODE_INTERACTIVE:
            // プロンプト待機中
            sa.sa_handler = signal_handler_interactive;
            sa.sa_flags = SA_RESTART;
            break;
            
        case MODE_HEREDOC:
            // ヒアドキュメント入力中
            sa.sa_handler = SIG_DFL;  // Ctrl+Cで中断可能
            sa.sa_flags = 0;
            break;
            
        case MODE_EXECUTING:
            // コマンド実行中
            sa.sa_handler = signal_handler_executing;
            sa.sa_flags = 0;
            break;
    }
    
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}
```

### 3. 子プロセスでのシグナル処理

```c
// src/executor/fork_exec.c

void child_process_setup(void)
{
    // デフォルトシグナルハンドラに戻す
    struct sigaction sa;
    
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    
    // 主要なシグナルをリセット
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    sigaction(SIGTTIN, &sa, NULL);
    sigaction(SIGTTOU, &sa, NULL);
}
```

### 4. シグナルセーフな処理

```c
// シグナルハンドラ内で使用可能な関数（抜粋）
// - write()
// - signal()
// - _exit()

// 使用不可な関数の例
// - printf()（バッファリングあり）
// - malloc()（非リエントラント）
// - readline関数（複雑な処理）

// シグナルセーフな実装例
void safe_signal_handler(int signum)
{
    const char msg[] = "Signal received\n";
    
    // writeはシグナルセーフ
    write(STDERR_FILENO, msg, sizeof(msg) - 1);
    
    // グローバル変数への単純な代入もOK
    g_signal_received = signum;
}
```

## シグナル番号と終了ステータス

### 主要なシグナル
| シグナル | 番号 | 説明 | 終了ステータス |
|----------|------|------|---------------|
| SIGINT | 2 | Ctrl+C | 130 (128+2) |
| SIGQUIT | 3 | Ctrl+\ | 131 (128+3) |
| SIGPIPE | 13 | パイプ破損 | 141 (128+13) |
| SIGTERM | 15 | 終了要求 | 143 (128+15) |

### 終了ステータスの計算
```c
// src/executor/wait_status.c
void update_exit_status_from_signal(int wstatus, t_shell *shell)
{
    if (WIFEXITED(wstatus))
    {
        // 正常終了
        shell->exit_status = WEXITSTATUS(wstatus);
    }
    else if (WIFSIGNALED(wstatus))
    {
        // シグナルによる終了
        int sig = WTERMSIG(wstatus);
        shell->exit_status = 128 + sig;
        
        // 特定のシグナルの場合メッセージ表示
        if (sig == SIGQUIT)
        {
            write(STDERR_FILENO, "Quit: 3\n", 8);
        }
        else if (sig == SIGINT)
        {
            write(STDERR_FILENO, "\n", 1);
        }
    }
}
```

## トラブルシューティング

### 1. シグナルが処理されない

```c
// シグナルマスクの確認
void debug_signal_mask(void)
{
    sigset_t current_mask;
    
    sigprocmask(SIG_BLOCK, NULL, &current_mask);
    
    if (sigismember(&current_mask, SIGINT))
        printf("SIGINT is blocked\n");
    if (sigismember(&current_mask, SIGQUIT))
        printf("SIGQUIT is blocked\n");
}
```

### 2. 二重シグナル処理

```c
// フラグで重複処理を防ぐ
static int processing_signal = 0;

void signal_handler(int signum)
{
    if (processing_signal)
        return;
        
    processing_signal = 1;
    // 処理
    processing_signal = 0;
}
```

### 3. readlineとの競合

```c
// readlineのシグナル処理を無効化
void setup_readline_signals(void)
{
    // readlineの内部シグナル処理を無効化
    rl_catch_signals = 0;
    
    // 独自のハンドラを設定
    setup_custom_signal_handlers();
}
```