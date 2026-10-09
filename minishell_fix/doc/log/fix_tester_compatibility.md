# minishell_tester 互換性修正

## 実施日時
2025年7月6日

## 問題の概要
commit cb66a67cafd9321f6059db8b8f5ba1cfd2418e59 の後、minishell_testerが全く通らなくなった。このコミット前は通っていたため、差分を分析して修正を実施。

## 原因
readline ライブラリが非対話型入力（パイプ経由）でも以下の動作をしていた：
- プロンプト（minishell$）を表示
- 入力コマンドをエコーバック

これにより、テスターが期待する出力と実際の出力が異なっていた。

## 修正内容

### main2.c の修正
非対話型モード（パイプ入力）の場合、readlineの出力を/dev/nullにリダイレクト：

```c
void	minishell_loop(char **envp)
{
	char	*line;

	init_signal();
	init_global_env(envp);
	if (!isatty(0))
		rl_outstream = fopen("/dev/null", "w");
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			handle_eof();
		if (*line)
		{
			add_history(line);
			process_line(line);
		}
		free(line);
	}
}
```

### handle_eof 関数の追加
norminette の25行制限に対応するため、EOF処理を別関数に分離：

```c
static void	handle_eof(void)
{
	if (isatty(0))
	{
		ft_putstr_fd("\033[1A\033[11C", 1);
		ft_putstr_fd("exit\n", 1);
	}
	cleanup_and_exit(g_exit_status);
}
```

## 結果

### テスト結果
```bash
$ echo "echo hello" | ./minishell
hello

$ printf "pwd\ncd ..\npwd\nexit\n" | ./minishell
/mnt/hgfs/42/42cursus/minishell
/mnt/hgfs/42/42cursus
```

- プロンプトとコマンドのエコーバックが表示されない
- 純粋な出力のみが表示される
- テスターが期待する動作を実現

### コンプライアンス
- **norminette**: 100% 通過
- **make**: 正常にビルド
- **minishell_tester**: 期待通りの動作

## 重要なポイント
1. `isatty(0)` を使用して対話型/非対話型を判別
2. 非対話型の場合、`rl_outstream` を `/dev/null` にリダイレクト
3. EOF時のエスケープシーケンス出力も対話型の場合のみに制限

これにより、minishell_testerが期待する出力形式を実現しながら、対話型使用時の体験も維持。