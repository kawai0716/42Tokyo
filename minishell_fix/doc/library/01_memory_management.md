# メモリ管理関数

## malloc

### プロトタイプ
```c
void *malloc(size_t size);
```

### ヘッダファイル
```c
#include <stdlib.h>
```

### 説明
指定されたサイズのメモリブロックを動的に割り当てます。

### パラメータ
- `size`: 割り当てるバイト数

### 戻り値
- 成功時: 割り当てられたメモリブロックへのポインタ
- 失敗時: NULL

### Minishellでの使用例

#### トークン構造体の割り当て
```c
// src/lexer/lexer.c
t_token *create_token(int type, char *value)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}
```

#### 文字列の複製
```c
// src/env/env_utils.c
char *duplicate_string(const char *str)
{
    char    *dup;
    size_t  len;
    
    if (!str)
        return (NULL);
    len = strlen(str);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    strcpy(dup, str);
    return (dup);
}
```

#### 配列の割り当て
```c
// src/parser/parse_cmd_utils.c
char **allocate_argv(int argc)
{
    char **argv;
    
    argv = malloc(sizeof(char *) * (argc + 1));
    if (!argv)
        return (NULL);
    argv[argc] = NULL;  // NULL終端
    return (argv);
}
```

### 注意点
- **NULL チェック必須**: mallocの戻り値は必ずチェック
- **サイズ計算**: sizeof演算子を使用して正確なサイズを計算
- **メモリリーク防止**: 対応するfreeを必ず実行
- **初期化**: mallocで確保したメモリは初期化されていない

---

## free

### プロトタイプ
```c
void free(void *ptr);
```

### ヘッダファイル
```c
#include <stdlib.h>
```

### 説明
mallocで割り当てられたメモリブロックを解放します。

### パラメータ
- `ptr`: 解放するメモリブロックへのポインタ（NULLも可）

### 戻り値
- なし

### Minishellでの使用例

#### 単一構造体の解放
```c
// src/lexer/lexer_utils.c
void free_token(t_token *token)
{
    if (!token)
        return;
    if (token->value)
        free(token->value);
    free(token);
}
```

#### リンクリストの解放
```c
// src/lexer/lexer.c
void free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;
    
    current = tokens;
    while (current)
    {
        next = current->next;
        free_token(current);
        current = next;
    }
}
```

#### 配列の解放
```c
// src/utils/cleanup.c
void free_string_array(char **array)
{
    int i;
    
    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
```

#### ASTの再帰的解放
```c
// src/parser/parser.c
void free_ast(t_node *node)
{
    if (!node)
        return;
    
    if (node->type == NODE_CMD)
    {
        free_string_array(node->u_data.cmd.argv);
    }
    else if (node->type == NODE_PIPE)
    {
        free_ast(node->u_data.pipe.left);
        free_ast(node->u_data.pipe.right);
    }
    else if (node->type == NODE_REDIR)
    {
        free(node->u_data.redir.filename);
        free_ast(node->u_data.redir.child);
    }
    free(node);
}
```

### 注意点

#### NULL ポインタの扱い
- `free(NULL)`は安全（何も起こらない）
- 防御的プログラミングとしてNULLチェックを推奨

#### 二重解放の防止
```c
// 悪い例
free(ptr);
free(ptr);  // 二重解放！未定義動作

// 良い例
free(ptr);
ptr = NULL;  // 解放後はNULLに設定
```

#### メモリリークパターンと対策

##### パターン1: エラーパスでの解放漏れ
```c
// 悪い例
t_node *create_node(void)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    
    node->data = malloc(100);
    if (!node->data)
        return (NULL);  // nodeがリーク！
    
    return (node);
}

// 良い例
t_node *create_node(void)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    
    node->data = malloc(100);
    if (!node->data)
    {
        free(node);  // エラー時も解放
        return (NULL);
    }
    
    return (node);
}
```

##### パターン2: 上書きによるリーク
```c
// 悪い例
char *str = malloc(10);
str = malloc(20);  // 最初の10バイトがリーク！

// 良い例
char *str = malloc(10);
free(str);
str = malloc(20);
```

### メモリ管理のベストプラクティス

1. **所有権の明確化**
   - 誰がメモリを割り当て、誰が解放するか明確にする
   - 関数のドキュメントに明記

2. **一貫したクリーンアップ関数**
   - 各構造体にfree関数を用意
   - 階層的な解放を実装

3. **valgrindでの検証**
```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./minishell
```

4. **早期リターン時の処理**
   - goto文を使用したクリーンアップ（42ノームで禁止）
   - 代わりに適切な条件分岐で対応

### Minishellでのメモリ管理戦略

#### 1. トークン化フェーズ
- 入力文字列からトークンを生成
- 各トークンは個別にmalloc
- エラー時は生成済みトークンを全て解放

#### 2. パース フェーズ
- トークンからASTを構築
- ASTノードは再帰的にmalloc
- パース失敗時はASTとトークンを両方解放

#### 3. 実行フェーズ
- 実行前にトークンを解放（ASTのみ保持）
- 実行後にASTを解放

#### 4. シェル終了時
- 全ての動的メモリを解放
- 環境変数リスト
- 入力バッファ
- その他の一時データ