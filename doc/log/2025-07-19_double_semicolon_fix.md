# 2025-07-19: ダブルセミコロン構文エラー修正

## 問題
solaldunckel-minishell-testerで `;; test` のテストが失敗していた。
- Bash: `syntax error near unexpected token ';;'`
- Minishell: (エラーメッセージなし)

## 原因
セミコロン区切りの処理（`process_line_with_semicolons`）が構文チェックより先に実行されていたため、`;;` が空のコマンド2つとして処理され、構文エラーが検出されなかった。

## 解決策
1. **`src/main2.c`**: `process_line` 関数で構文チェックを先に実行
   - レキサーでトークン化
   - `validate_syntax` で構文検証
   - 構文エラーがあれば処理を中断
   - 構文が正しい場合のみセミコロン処理へ

2. **`src/parser.c`**: ダブルセミコロンの検出を追加
   - `validate_token_sequence` 関数でセミコロンの次のトークンもチェック
   - 次もセミコロンの場合は `;;` エラーを報告

## 修正後の動作
- `;; test` → `syntax error near unexpected token ';'`
- `test ;;` → `syntax error near unexpected token ';;'`
- `;` → `syntax error near unexpected token ';'`
- `; ;` → `syntax error near unexpected token ';'`

## 影響
- bashと同じ構文エラー検出を実現
- 既存の機能（変数代入、空変数展開など）は正常に動作
- solaldunckel-minishell-testerの `;; test` テストが通過