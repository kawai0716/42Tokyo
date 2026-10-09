# Ctrl+C送信時のプロンプト重複表示問題修正ログ

## 日付: 2025-08-03

## 問題の内容
インタラクティブモードでコマンドの実行中にCtrl+Cを送信すると、プロンプトが複数表示される問題が発生していた。

## 原因
`src/signal/signal.c`のシグナルハンドラー内で、コマンド実行中でもreadline関数（`rl_on_new_line()`, `rl_replace_line()`, `rl_redisplay()`）を呼び出していたことが原因。

シグナルハンドラーは非同期的に実行されるため、コマンド実行中にこれらの関数を呼び出すと、メインループでのプロンプト表示と競合して複数のプロンプトが表示される。

## 修正内容

### 1. シグナルハンドラーの修正
`signal_handler()`関数から、readline関数の呼び出しを削除。改行の出力のみ残した。

```c
static void	signal_handler(int signum)
{
	g_signal_received = signum;
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		// readline関数はここでは呼び出さない
		// メインループでシェルモードに応じて適切に処理する
	}
}
```

### 2. handle_signal()関数の更新
`handle_signal()`関数で、シェルモードに応じた適切な処理を行うように修正。
- MODE_INTERACTIVE: readline関数を呼び出してプロンプトを再表示
- MODE_EXECUTING: exit_statusの設定のみ（改行は既にハンドラで出力済み）

```c
void	handle_signal(t_shell *shell)
{
	int	sig;

	sig = g_signal_received;
	g_signal_received = 0;
	if (sig == SIGINT)
	{
		if (shell->shell_mode == MODE_INTERACTIVE)
		{
			// インタラクティブモードではreadline関数を呼び出す
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			shell->exit_status = 130;
		}
		else if (shell->shell_mode == MODE_EXECUTING)
		{
			// 実行中は改行は既にハンドラで出力済み
			// exit_statusの設定のみ
			shell->exit_status = 130;
		}
	}
}
```

## 修正の効果
シグナルハンドラー内でのreadline関数呼び出しを避けることで、プロンプトの重複表示問題が解決される。シェルモードに応じた適切な処理により、インタラクティブモードとコマンド実行中の両方で正しい動作が期待できる。

## テスト方法
1. `./minishell`を起動
2. `sleep 5`などの長時間実行されるコマンドを入力
3. 実行中にCtrl+Cを押下
4. プロンプトが1つだけ表示されることを確認