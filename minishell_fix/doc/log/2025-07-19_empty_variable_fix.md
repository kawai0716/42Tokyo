# 2025-07-19: 空変数展開時のスペース処理修正

## 問題
solaldunckel-minishell-testerで `echo    $TEST lol $TEST` のテストが失敗していた。
- Minishell: ` lol ` (前後にスペースあり)
- Bash: `lol` (スペースなし)

## 原因
bashでは、変数が空文字列に展開される場合（未定義または空文字列）、その変数は単語として扱われず、周囲の空白も削除される。

## 解決策
`src/lexer3.c` の `parse_word` 関数を修正：
1. 引用符で囲まれた部分（`""` や `''`）は常に単語として扱う（`has_content = 1`）
2. 引用符外の部分は、実際に内容がある場合のみ単語として扱う
3. 単語全体が空で、引用符部分がない場合は、その単語をレキサーに追加しない

### 実装の詳細
```c
// parse_word 関数内
int has_content = 0;
while (...) {
    if (引用符) {
        has_content = 1;  // 引用符は常に内容として扱う
    } else {
        if (part && part[0] != '\0')
            has_content = 1;  // 実際の内容がある場合のみ
    }
}
if (!has_content && result && result[0] == '\0') {
    free(result);
    return (NULL);  // 空の単語は作らない
}
```

## 結果
- `echo    $TEST lol $TEST` → `lol` (正しい)
- `echo test "" test "" test` → `test  test  test` (空引用符は保持)
- `echo $TEST $TEST` → (空出力、正しい)

## 影響
この修正により、bashと同じ動作を実現：
- 空変数展開時の余分なスペースが削除される
- 空の引用符（`""`）は正しく空文字列として保持される
- セミコロン区切りの変数代入も正しく動作