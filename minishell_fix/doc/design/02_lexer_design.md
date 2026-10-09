# Lexer（字句解析器）設計

## 1. 概要

レキサーは入力文字列をトークン列に変換する役割を担います。シェルコマンドの構文要素を識別し、後続のパーサーが処理しやすい形式に変換します。

## 2. トークン定義

### 2.1 トークン種別

```c
#define TOKEN_WORD          0  // 通常の単語
#define TOKEN_PIPE          1  // パイプ |
#define TOKEN_REDIR_IN      2  // 入力リダイレクション <
#define TOKEN_REDIR_OUT     3  // 出力リダイレクション >
#define TOKEN_REDIR_APPEND  4  // 追記リダイレクション >>
#define TOKEN_HEREDOC       5  // ヒアドキュメント <<
#define TOKEN_SEMICOLON     6  // セミコロン ;
```

### 2.2 トークン構造体

```c
typedef struct s_token {
    int             type;    // トークン種別
    char            *value;  // トークン値
    struct s_token  *next;   // 次のトークンへのポインタ
} t_token;
```

## 3. 字句解析プロセス

### 3.1 処理フロー

```
入力文字列
    ↓
文字単位の走査
    ↓
トークン識別
    ↓
クォート処理
    ↓
変数展開
    ↓
ワイルドカード展開
    ↓
トークン列生成
```

### 3.2 主要ファイルと関数

#### lexer.c
- レキサーのメインエントリポイント
- トークン化の全体制御

#### lexer_parse.c
- トークンの解析と分類
- 演算子の識別

#### lexer_expand.c
- 変数展開の制御
- 展開済み文字列の生成

#### lexer_var.c
- 環境変数の展開処理
- $変数、$?の処理

#### lexer_var_split.c
- 変数展開後の単語分割
- IFS（Internal Field Separator）処理

#### lexer_quotes.c
- クォート処理（シングル、ダブル）
- クォート内の特殊文字処理

#### lexer_word.c
- 単語トークンの処理
- ワイルドカード展開の呼び出し

#### lexer_utils.c
- ユーティリティ関数
- メタ文字判定、空白判定

## 4. クォート処理

### 4.1 シングルクォート（'）
- 内部の文字をリテラルとして扱う
- 変数展開を行わない
- エスケープ文字も無効

```bash
echo 'Hello $USER'  # 出力: Hello $USER
```

### 4.2 ダブルクォート（"）
- 変数展開を行う
- 特定の文字（$, `, \, "）のエスケープが有効
- 空白文字を保持

```bash
echo "Hello $USER"  # 出力: Hello username
```

### 4.3 エスケープ文字（\）
- 次の文字を特殊文字として扱わない
- クォート外でメタ文字をエスケープ

```bash
echo Hello\ World  # 出力: Hello World
```

## 5. 変数展開

### 5.1 環境変数展開
```c
// $VARIABLEの形式を展開
char *expand_env_var(char *var_name, t_shell *shell) {
    char *value = getenv(var_name);
    return value ? ft_strdup(value) : ft_strdup("");
}
```

### 5.2 特殊変数
- `$?`: 直前のコマンドの終了ステータス
- `$$`: 現在のプロセスID（未実装）
- `$0`: シェル名（未実装）

### 5.3 展開ルール
1. ダブルクォート内では展開
2. シングルクォート内では展開しない
3. 変数名は英数字とアンダースコアのみ

## 6. ワイルドカード展開

### 6.1 サポートするパターン
- `*`: 0文字以上の任意の文字列
- `?`: 任意の1文字（ボーナス機能）

### 6.2 展開処理
```c
// ワイルドカードパターンをファイル名に展開
t_token *expand_wildcard(char *pattern) {
    // ディレクトリ内のファイルを検索
    // パターンにマッチするファイルをトークン化
    // マッチしない場合はパターンをそのまま返す
}
```

## 7. メタ文字処理

### 7.1 メタ文字の定義
```c
int is_metachar(char c) {
    return (c == '|' || c == '<' || c == '>' || 
            c == ';' || c == '&' || c == '(' || 
            c == ')' || c == ' ' || c == '\t');
}
```

### 7.2 演算子の識別
- 単一文字演算子: `|`, `<`, `>`, `;`
- 複数文字演算子: `>>`, `<<`, `&&`, `||`

## 8. エラー処理

### 8.1 構文エラー
- 閉じられていないクォート
- 不正な演算子の配置
- 予期しないトークン

### 8.2 エラーメッセージ
```c
void print_syntax_error(char *token) {
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putstr_fd("'\n", 2);
}
```

## 9. 最適化と効率性

### 9.1 文字列バッファ管理
- 動的バッファの使用
- 必要に応じた再割り当て
- メモリリークの防止

### 9.2 トークンリスト管理
- 連結リストによる効率的な追加
- 適切なメモリ解放

## 10. テストケース

### 10.1 基本的なトークン化
```bash
入力: echo hello world
トークン: [WORD:"echo"] [WORD:"hello"] [WORD:"world"]
```

### 10.2 パイプとリダイレクション
```bash
入力: cat < input.txt | grep pattern > output.txt
トークン: [WORD:"cat"] [REDIR_IN:"<"] [WORD:"input.txt"] 
         [PIPE:"|"] [WORD:"grep"] [WORD:"pattern"] 
         [REDIR_OUT:">"] [WORD:"output.txt"]
```

### 10.3 クォートと変数展開
```bash
入力: echo "Hello $USER" 'Literal $USER'
トークン: [WORD:"echo"] [WORD:"Hello username"] [WORD:"Literal $USER"]
```

## 11. 実装の詳細

### 11.1 状態遷移
レキサーは以下の状態を持ちます：
- NORMAL: 通常状態
- IN_WORD: 単語読み取り中
- IN_SINGLE_QUOTE: シングルクォート内
- IN_DOUBLE_QUOTE: ダブルクォート内

### 11.2 バッファ管理
```c
typedef struct s_lexer_state {
    char    *input;      // 入力文字列
    int     pos;         // 現在位置
    char    *buffer;     // トークンバッファ
    int     buf_size;    // バッファサイズ
    int     buf_pos;     // バッファ位置
    int     quote_state; // クォート状態
} t_lexer_state;
```

## 12. 制限事項と考慮事項

### 12.1 制限事項
- ネストしたクォートの処理
- 複雑なパラメータ展開（${VAR:-default}等）は未対応
- ブレース展開は未対応

### 12.2 bashとの互換性
- 基本的な字句解析はbash互換
- 一部の高度な機能は未実装
- エラーメッセージはbashに準拠