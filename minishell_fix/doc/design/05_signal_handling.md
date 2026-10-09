# Signal Handling（シグナル処理）設計

## 1. 概要

Minishellのシグナル処理は、インタラクティブシェルとしての適切な動作を保証します。Ctrl+C、Ctrl+D、Ctrl+\などのキーボード割り込みを処理し、bashと同様の動作を実現します。

## 2. シグナル処理の要件

### 2.1 42プロジェクトの要件

- **Ctrl+C (SIGINT)**: 新しい行に新しいプロンプトを表示
- **Ctrl+D (EOF)**: シェルを終了
- **Ctrl+\ (SIGQUIT)**: インタラクティブモードでは何もしない
- **グローバル変数**: シグナル番号格納用に1つのみ許可

### 2.2 動作モード別の処理

```c
// シェルの動作モード
#define MODE_INTERACTIVE  0  // プロンプト待機中
#define MODE_HEREDOC      1  // ヒアドキュメント入力中
#define MODE_EXECUTING    2  // コマンド実行中

// グローバル変数（唯一許可されている）
volatile sig_atomic_t g_signal_received = 0;
```

## 3. シグナルハンドラの実装

### 3.1 メインシグナルハンドラ

主要なシグナルハンドラは`src/signal/signal_handler.c`に実装されています。

```c
// インタラクティブモード用ハンドラ
void signal_handler_interactive(int signum) {
    g_signal_received = signum;
    
    if (signum == SIGINT) {
        // 新しい行に移動
        write(STDERR_FILENO, "\n", 1);
        
        // readlineのプロンプトを再表示
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

// 実行モード用ハンドラ
void signal_handler_executing(int signum) {
    g_signal_received = signum;
    // 親プロセスは基本的に何もしない
}
```

### 3.2 モード別ハンドラ設定

シグナル設定は`src/signal/signal.c`で管理されています。

```c
// インタラクティブモード用のシグナル設定
void init_signal(void) {
    struct sigaction sa;
    
    sa.sa_handler = signal_handler_interactive;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    
    signal(SIGQUIT, SIG_IGN);
}

// 実行モード用のシグナル設定
void set_execution_signal(void) {
    struct sigaction sa;
    
    sa.sa_handler = signal_handler_executing;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    
    signal(SIGQUIT, SIG_IGN);
}

// インタラクティブモードへの復帰
void restore_interactive_signal(void) {
    init_signal();
}
```

## 4. モード別の詳細動作

### 4.1 インタラクティブモード（MODE_INTERACTIVE）

```c
// プロンプト待機中の動作
void handle_interactive_mode(t_shell *shell) {
    setup_signals(MODE_INTERACTIVE);
    
    char *line = readline("minishell$ ");
    
    if (g_signal_received == SIGINT) {
        g_signal_received = 0;
        shell->exit_status = 130;  // 128 + SIGINT(2)
        // プロンプトは既に再表示されている
    }
    
    if (!line) {  // Ctrl+D (EOF)
        ft_putstr_fd("exit\n", STDERR_FILENO);
        exit(shell->exit_status);
    }
}
```

### 4.2 実行モード（MODE_EXECUTING）

```c
// コマンド実行中の動作
void handle_execution_mode(t_shell *shell) {
    pid_t pid = fork();
    
    if (pid == 0) {  // 子プロセス
        // デフォルトシグナルハンドラに戻す
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        
        // コマンド実行
        execve(cmd_path, argv, envp);
    } else {  // 親プロセス
        // 親はSIGINTを無視
        setup_signals(MODE_EXECUTING);
        
        int status;
        waitpid(pid, &status, 0);
        
        // シグナルで終了した場合の処理
        if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            shell->exit_status = 128 + sig;
            
            if (sig == SIGQUIT) {
                ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
            } else if (sig == SIGINT) {
                ft_putstr_fd("\n", STDERR_FILENO);
            }
        }
        
        // インタラクティブモードに戻す
        setup_signals(MODE_INTERACTIVE);
    }
}
```

### 4.3 ヒアドキュメントモード（MODE_HEREDOC）

```c
// ヒアドキュメント入力中の動作
void handle_heredoc_mode(t_shell *shell) {
    pid_t pid = fork();
    
    if (pid == 0) {  // 子プロセス（ヒアドキュメント入力処理）
        // SIGINTをデフォルトに設定（Ctrl+Cで終了可能）
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        
        char *line;
        while ((line = readline("> "))) {
            if (strcmp(line, delimiter) == 0) {
                free(line);
                break;
            }
            // パイプに書き込み
            write(pipe_fd, line, strlen(line));
            write(pipe_fd, "\n", 1);
            free(line);
        }
        
        if (!line) {  // Ctrl+D
            // EOFの処理（改行は出力しない）
        }
        
        exit(0);
    } else {  // 親プロセス
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) {
            // Ctrl+Cで中断された
            shell->exit_status = 130;
            ft_putstr_fd("\n", STDERR_FILENO);
            return -1;  // ヒアドキュメント失敗
        }
    }
}
```

## 5. Readline統合

### 5.1 Readlineシグナル設定

```c
void setup_readline_signals(void) {
    // ReadlineのデフォルトシグナルハンドラをカスタマイズBb
    rl_catch_signals = 0;  // Readlineの内部シグナル処理を無効化
    
    // カスタムハンドラを設定
    rl_signal_event_hook = check_signal_status;
}

int check_signal_status(void) {
    if (g_signal_received) {
        // シグナルを処理
        handle_pending_signal();
        g_signal_received = 0;
    }
    return 0;
}
```

### 5.2 Readlineコールバック

```c
// Ctrl+Cが押された時のreadline処理
void rl_sigint_handler(void) {
    rl_done = 1;  // readline入力を終了
    rl_cleanup_after_signal();
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
```

## 6. 終了ステータス管理

### 6.1 シグナル関連の終了ステータス

```c
// シグナルによる終了ステータスの計算
int get_signal_exit_status(int signum) {
    return 128 + signum;
}

// 主要なシグナル終了ステータス
#define EXIT_SIGINT  130  // 128 + SIGINT(2)
#define EXIT_SIGQUIT 131  // 128 + SIGQUIT(3)
#define EXIT_SIGTERM 143  // 128 + SIGTERM(15)
```

### 6.2 ステータス更新

```c
void update_exit_status_from_signal(int status, t_shell *shell) {
    if (WIFSIGNALED(status)) {
        shell->exit_status = 128 + WTERMSIG(status);
    } else if (WIFEXITED(status)) {
        shell->exit_status = WEXITSTATUS(status);
    }
}
```

## 7. 並行処理での考慮事項

### 7.1 競合状態の回避

```c
// シグナルセーフな処理
volatile sig_atomic_t g_signal_received = 0;

// シグナルハンドラ内では最小限の処理のみ
void minimal_signal_handler(int signum) {
    g_signal_received = signum;  // atomic操作
}

// 実際の処理はメインループで
void process_pending_signals(t_shell *shell) {
    if (g_signal_received) {
        int sig = g_signal_received;
        g_signal_received = 0;
        
        // ここで実際の処理を行う
        handle_signal(sig, shell);
    }
}
```

### 7.2 子プロセスでのシグナルリセット

```c
void reset_signals_in_child(void) {
    // 全てのシグナルをデフォルトに戻す
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}
```

## 8. エラー処理

### 8.1 シグナル設定エラー

```c
int setup_signal_handler(int signum, void (*handler)(int)) {
    struct sigaction sa;
    
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    
    if (sigaction(signum, &sa, NULL) == -1) {
        perror("sigaction");
        return -1;
    }
    
    return 0;
}
```

## 9. テストシナリオ

### 9.1 インタラクティブモードテスト

```bash
# Ctrl+C テスト
$ sleep 10
^C
$ echo $?
130

# Ctrl+\ テスト（何も起こらない）
$ sleep 10
^\
（sleepが継続）

# Ctrl+D テスト
$ ^D
exit
```

### 9.2 ヒアドキュメントテスト

```bash
# 正常終了
$ cat << EOF
> hello
> world
> EOF
hello
world

# Ctrl+C で中断
$ cat << EOF
> hello
^C
$ echo $?
130

# Ctrl+D で終了
$ cat << EOF
> hello
> ^D
hello
```

## 10. デバッグとトラブルシューティング

### 10.1 シグナル状態の確認

```c
void debug_signal_state(void) {
    struct sigaction sa;
    
    sigaction(SIGINT, NULL, &sa);
    printf("SIGINT handler: %p\n", sa.sa_handler);
    
    sigaction(SIGQUIT, NULL, &sa);
    printf("SIGQUIT handler: %p\n", sa.sa_handler);
}
```

### 10.2 一般的な問題と解決策

| 問題 | 原因 | 解決策 |
|------|------|--------|
| Ctrl+Cが効かない | シグナルがブロックされている | sigprocmaskで確認 |
| プロンプトが壊れる | readline状態の不整合 | rl_cleanup_after_signal使用 |
| 子プロセスが残る | シグナルが伝播しない | プロセスグループ設定 |
| 終了ステータスが間違っている | シグナル処理の誤り | WIFSIGNALED確認 |

## 11. bashとの互換性

### 11.1 bashの動作

- インタラクティブモード：Ctrl+Cで現在の入力をキャンセル
- 実行中：Ctrl+Cでプロセスを終了
- ヒアドキュメント：Ctrl+Cで入力を中断

### 11.2 Minishellでの実装

同様の動作を実現するため、モード管理とシグナルハンドラの切り替えを実装