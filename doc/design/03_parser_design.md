# Parser（構文解析器）設計

## 1. 概要

パーサーはレキサーが生成したトークン列を抽象構文木（AST: Abstract Syntax Tree）に変換します。シェルコマンドの構造を解析し、実行可能な形式に組み立てます。

## 2. AST（抽象構文木）構造

### 2.1 ノード種別

```c
#define NODE_CMD        0  // コマンドノード
#define NODE_PIPE       1  // パイプノード
#define NODE_REDIR      2  // リダイレクションノード
#define NODE_SEMICOLON  3  // セミコロンノード
```

### 2.2 ノード構造体

```c
typedef struct s_node {
    int type;  // ノード種別
    union {
        t_cmd       cmd;       // コマンドデータ
        t_pipe      pipe;      // パイプデータ
        t_redir     redir;     // リダイレクションデータ
        t_semicolon semicolon; // セミコロンデータ
    } u_data;
} t_node;
```

### 2.3 各ノードの詳細構造

```c
// コマンドノード
typedef struct s_cmd {
    char    **argv;      // 引数配列
    int     argc;        // 引数の数
} t_cmd;

// パイプノード
typedef struct s_pipe {
    t_node  *left;   // 左側のコマンド
    t_node  *right;  // 右側のコマンド
} t_pipe;

// リダイレクションノード
typedef struct s_redir {
    int     redir_type;  // リダイレクション種別
    char    *filename;   // ファイル名/区切り文字
    t_node  *child;      // 子ノード
    int     heredoc_fd;  // ヒアドキュメント用FD
} t_redir;

// セミコロンノード
typedef struct s_semicolon {
    t_node  *left;   // 左側のコマンド
    t_node  *right;  // 右側のコマンド
} t_semicolon;
```

## 3. 構文解析アルゴリズム

### 3.1 再帰下降構文解析

パーサーは再帰下降構文解析法を採用しています。各構文要素に対応する関数が再帰的に呼び出されます。

```
parse_line()
    ├── parse_pipeline()
    │   ├── parse_command()
    │   │   ├── parse_simple_command()
    │   │   └── parse_redirections()
    │   └── parse_pipe_sequence()
    └── parse_semicolon_sequence()
```

### 3.2 優先順位

1. セミコロン（;） - 最低優先順位
2. パイプ（|）
3. リダイレクション（<, >, >>, <<）
4. コマンドと引数 - 最高優先順位

## 4. 主要ファイルと解析関数

### 4.1 parser.c
- メインパーサーのエントリポイント
- 全体的な解析フローの制御

### 4.2 parse_pipeline.c
- パイプライン構造の解析
- パイプで連結されたコマンドの処理

### 4.3 parse_command.c
- 単一コマンドの解析
- 引数とリダイレクションの処理

### 4.4 parse_cmd_utils.c
- コマンド解析のユーティリティ関数
- トークンからの引数配列生成

### 4.5 parse_redir.c
- リダイレクション演算子の解析
- ファイル名やヒアドキュメント区切り文字の処理

### 4.6 parse_semicolon.c
- セミコロン区切りのコマンド列解析
- 複数コマンドの連続実行構造の生成

```c
// パイプライン解析
t_node *parse_pipeline(t_token **tokens, t_shell *shell) {
    t_node *left = parse_command(tokens, shell);
    
    while (*tokens && (*tokens)->type == TOKEN_PIPE) {
        *tokens = (*tokens)->next;  // '|'をスキップ
        t_node *right = parse_pipeline(tokens, shell);
        left = create_pipe_node(left, right);
    }
    return left;
}
```

### 4.3 parse_command.c

```c
// コマンド解析
t_node *parse_command(t_token **tokens, t_shell *shell) {
    t_node *node = NULL;
    t_list *args = NULL;
    
    while (*tokens && is_command_token(*tokens)) {
        if (is_redirection(*tokens)) {
            node = parse_redirection(tokens, node, shell);
        } else {
            add_argument(&args, (*tokens)->value);
            *tokens = (*tokens)->next;
        }
    }
    
    if (args && !node)
        node = create_cmd_node(args);
    
    return node;
}
```

### 4.4 parse_redir.c

```c
// リダイレクション解析
t_node *parse_redirection(t_token **tokens, t_node *child, t_shell *shell) {
    int redir_type = get_redir_type((*tokens)->type);
    *tokens = (*tokens)->next;  // リダイレクション記号をスキップ
    
    if (!*tokens || (*tokens)->type != TOKEN_WORD) {
        print_syntax_error("newline");
        return NULL;
    }
    
    char *filename = ft_strdup((*tokens)->value);
    *tokens = (*tokens)->next;
    
    return create_redir_node(redir_type, filename, child);
}
```

## 5. AST構築例

### 5.1 単純なコマンド

```bash
入力: echo hello world
```

```
    CMD
     ├─ argv[0]: "echo"
     ├─ argv[1]: "hello"
     └─ argv[2]: "world"
```

### 5.2 パイプライン

```bash
入力: cat file.txt | grep pattern | wc -l
```

```
         PIPE
        /     \
     PIPE      CMD
    /    \      └─ ["wc", "-l"]
  CMD     CMD
   └─ ["cat",  └─ ["grep", 
      "file.txt"]  "pattern"]
```

### 5.3 リダイレクション

```bash
入力: echo hello > output.txt
```

```
      REDIR(>)
         │
         ├─ filename: "output.txt"
         └─ child: CMD
                    └─ ["echo", "hello"]
```

### 5.4 複合構造

```bash
入力: cat < input.txt | grep pattern > output.txt
```

```
           PIPE
          /     \
    REDIR(<)    REDIR(>)
        │           │
        ├─ "input.txt"  ├─ "output.txt"
        └─ CMD          └─ CMD
            └─ ["cat"]      └─ ["grep", "pattern"]
```

## 6. エラー処理

### 6.1 構文エラーの検出

- 予期しないトークン
- パイプの後にコマンドがない
- リダイレクションの後にファイル名がない
- 閉じられていない構造

### 6.2 エラー回復

```c
void handle_parse_error(t_token *token, t_shell *shell) {
    print_syntax_error(token ? token->value : "newline");
    shell->exit_status = 2;  // bashと同じ構文エラーコード
    // ASTの部分的なクリーンアップ
    // パースを中断
}
```

## 7. メモリ管理

### 7.1 ASTノードの作成

```c
t_node *create_node(int type) {
    t_node *node = ft_calloc(1, sizeof(t_node));
    if (!node)
        return NULL;
    node->type = type;
    return node;
}
```

### 7.2 ASTの解放

```c
void cleanup_ast(t_node *node) {
    if (!node)
        return;
    
    switch (node->type) {
        case NODE_CMD:
            free_string_array(node->u_data.cmd.argv);
            break;
        case NODE_PIPE:
            cleanup_ast(node->u_data.pipe.left);
            cleanup_ast(node->u_data.pipe.right);
            break;
        case NODE_REDIR:
            free(node->u_data.redir.filename);
            cleanup_ast(node->u_data.redir.child);
            break;
        case NODE_SEMICOLON:
            cleanup_ast(node->u_data.semicolon.left);
            cleanup_ast(node->u_data.semicolon.right);
            break;
    }
    free(node);
}
```

## 8. 最適化と効率性

### 8.1 左再帰の回避

左再帰を避けるため、繰り返し構造を使用：

```c
// 左再帰を避けた実装
t_node *parse_pipe_sequence(t_token **tokens, t_shell *shell) {
    t_node *left = parse_command(tokens, shell);
    
    while (*tokens && (*tokens)->type == TOKEN_PIPE) {
        // 繰り返しによる処理
    }
    return left;
}
```

### 8.2 先読み（Lookahead）

必要最小限の先読みで効率的な解析：

```c
int peek_token_type(t_token *token) {
    return token ? token->type : -1;
}
```

## 9. 拡張性

### 9.1 新しいノード種別の追加

新しい構文要素を追加する場合：

1. ノード種別を定義
2. ノード構造体を追加
3. パース関数を実装
4. cleanup関数を更新

### 9.2 演算子の優先順位

優先順位テーブルによる管理：

```c
int get_operator_precedence(int token_type) {
    switch (token_type) {
        case TOKEN_SEMICOLON: return 1;
        case TOKEN_PIPE:      return 2;
        case TOKEN_REDIR_IN:
        case TOKEN_REDIR_OUT:
        case TOKEN_REDIR_APPEND:
        case TOKEN_HEREDOC:   return 3;
        default:              return 0;
    }
}
```

## 10. テストと検証

### 10.1 パーサーテスト

test/parser/ディレクトリに包括的なテストケース：

- 基本的なコマンド解析
- パイプライン解析
- リダイレクション解析
- エラーケース

### 10.2 AST可視化

デバッグ用のAST表示関数：

```c
void print_ast(t_node *node, int depth) {
    if (!node) return;
    
    for (int i = 0; i < depth; i++)
        printf("  ");
    
    switch (node->type) {
        case NODE_CMD:
            printf("CMD: ");
            for (int i = 0; node->u_data.cmd.argv[i]; i++)
                printf("[%s] ", node->u_data.cmd.argv[i]);
            printf("\n");
            break;
        // 他のノード種別...
    }
}
```

## 11. bashとの互換性

### 11.1 サポートする構文

- 基本的なコマンド実行
- パイプライン
- 入出力リダイレクション
- ヒアドキュメント
- セミコロン区切り

### 11.2 未サポートの構文

- サブシェル ()
- コマンド置換 $()、``
- 条件分岐 if/then/else
- ループ構造 for/while
- 関数定義