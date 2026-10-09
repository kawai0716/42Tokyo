# 2025-07-19: セミコロン区切りコマンドでの変数代入修正

## 問題
solaldunckel-minishell-testerで64/70のテストしか通っていなかった。主な問題は以下：
- `A=hello; echo $A` のようなセミコロン区切りコマンドで変数が引き継がれない
- `export TEST=LOL ; echo $TEST` で変数が表示されない

## 原因
minishellの実装では、変数展開がレキサー（字句解析）段階で行われていた：
1. `process_line`が`A=hello; echo $A`を受け取る
2. レキサーが**行全体**を一度に字句解析
3. この時点で`$A`を展開しようとするが、`A`はまだ設定されていない（実行前のため）
4. `$A`は空文字列に展開される
5. その後実行されて`A=hello`が設定されるが、既に遅い

## 解決策
セミコロンで区切られたコマンドを個別に処理するように変更：

### 実装
1. `src/main4.c`を新規作成
   - `find_unquoted_semicolon`: 引用符外のセミコロンを探す
   - `extract_command`: コマンドを抽出
   - `process_line_with_semicolons`: セミコロンで分割して順次処理
   - `process_single_command`: 単一コマンドを処理

2. `src/main2.c`を修正
   - `process_line`を`process_line_with_semicolons`を呼ぶように変更
   - `handle_parse_error`と`handle_lexer_error`をstaticから通常の関数に変更

### 結果
```bash
# 修正前
$ echo 'A=hello; echo $A' | ./minishell
（空出力）

# 修正後
$ echo 'A=hello; echo $A' | ./minishell
hello
```

## 影響
- セミコロン区切りの変数代入が正しく動作
- `export`コマンドも期待通り動作
- `+=`演算子も正しく動作
- 複数の変数代入も機能

## 残課題
- `${VAR}`形式の変数展開はまだ未対応
- solaldunckel-minishell-testerの最終結果確認が必要