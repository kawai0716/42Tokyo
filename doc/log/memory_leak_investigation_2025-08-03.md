# メモリリーク調査レポート (2025-08-03)

## 調査結果サマリー

現在のminishellでの"still reachable"メモリリークの状況：

### パイプコマンド実行時のみ発生
- **リーク量**: 30バイト (2ブロック、各15バイト)
- **発生条件**: パイプを含むコマンド実行時の子プロセス内
- **影響**: プログラムの動作には影響なし（子プロセス終了時に解放される）

## 詳細分析

### 1. リークが発生するケース
```bash
echo "ls | grep test" | valgrind ./minishell
```
- 子プロセス（PID: 94555, 94557）で各15バイトが2箇所でリーク

### 2. リークが発生しないケース
- 単純なexit: リークなし
- echoコマンド: リークなし  
- リダイレクション: リークなし
- 環境変数操作: リークなし
- 複数コマンド（&&使用）: リークなし
- エラーケース: リークなし

### 3. リークの発生箇所

#### 箇所1: get_next_line_minishell内
```
ft_substr (in minishell)
extract_line_and_save_leftover (in minishell)
get_next_line_minishell (in minishell)
non_interactive_loop (in minishell)
minishell_loop (in minishell)
main (in minishell)
```

#### 箇所2: process_line_with_semicolons内
```
ft_substr (in minishell)
extract_command (in minishell)
process_line_with_semicolons (in minishell)
process_line (in minishell)
non_interactive_loop (in minishell)
minishell_loop (in minishell)
main (in minishell)
```

## テスト結果

minishell_testerの実行結果：
- **146/146テスト合格** 🎉
- 全機能が正常に動作

## 結論

1. **影響度**: 低
   - 子プロセス内でのみ発生
   - プロセス終了時にOSが自動的に解放
   - 親プロセス（メインのminishell）ではリークなし

2. **原因**: 
   - non_interactive_loop内でのget_next_line処理
   - コマンド解析時のft_substr使用
   - 子プロセスでの終了処理が不完全

3. **推奨対応**:
   - 優先度は低い（実用上の問題なし）
   - 必要であれば子プロセス終了前のクリーンアップ処理を追加

## 参考: Valgrindコマンド
```bash
# メモリリーク検査
echo "コマンド" | valgrind --leak-check=full --show-leak-kinds=all ./minishell

# 子プロセスも含めて検査（非推奨：minishellの引数処理の問題あり）
valgrind --trace-children=yes ./minishell
```