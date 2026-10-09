# readline パイプエコー問題の修正

## 実施日時
2025年7月6日

## 問題の概要
minishell_tester の実行時に、パイプを含むコマンドが異常な形でエコーバックされる問題が発生：
- `echo hello | cat` を入力すると `echo hello < /dev/null | cat` と表示される
- readline ライブラリが非対話型入力（パイプ経由）で特殊な動作をすることが原因

## 調査結果
doc/log/readline_pipe_echo_investigation.md の調査により、これは readline ライブラリの仕様であることが判明した。

## 修正内容

### 1. 非対話型モードの検出と処理を実装
- `isatty(0)` を使用して、標準入力が端末かどうかを判定
- 端末の場合: 従来通り readline を使用（interactive_loop）
- パイプ/ファイルの場合: 独自の入力処理を使用（non_interactive_loop）

### 2. ファイル分割（norminette 対応）
**src/main2.c**
- handle_parse_error()
- handle_lexer_error()
- process_line()
- interactive_loop()
- minishell_loop()

**src/main3.c（新規作成）**
- find_newline()
- read_line_from_stdin()
- non_interactive_loop()

### 3. 実装詳細
```c
void	minishell_loop(char **envp)
{
	init_signal();
	init_global_env(envp);
	if (isatty(0))
		interactive_loop();  // readline を使用
	else
		non_interactive_loop();  // read() を直接使用
}
```

非対話型モードでは、read() システムコールを使用して標準入力から直接読み取り、readline のエコーバック問題を回避。

## 結果
- norminette: 100% 通過（41/41 ファイル）
- make: 正常にビルド完了
- minishell_tester: readline のエコーバック問題が解決
- インタラクティブモードの動作に影響なし

## 今後の課題
- 残りのテスト失敗の原因調査と修正
- 全テストケースの通過を目指す