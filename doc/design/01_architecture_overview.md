# Minishell アーキテクチャ概要

## 1. プロジェクト概要

Minishellは、42スクールのプロジェクトとして開発されたUnixシェルの実装です。bashの基本機能を模倣し、コマンド実行、パイプライン、リダイレクション、ビルトインコマンドなどの機能を提供します。

## 2. アーキテクチャ設計

### 2.1 レイヤー構造

```
┌─────────────────────────────────────────┐
│          Main Loop (shell_loop.c)       │
├─────────────────────────────────────────┤
│         Process Line (process_line.c)   │
├─────────┬───────────┬───────────────────┤
│  Lexer  │  Parser   │     Executor      │
├─────────┴───────────┴───────────────────┤
│    Environment    │    Signal Handler    │
├───────────────────┴─────────────────────┤
│              libft (Utilities)          │
└─────────────────────────────────────────┘
```

### 2.2 処理フロー

```
入力 → レキサー → パーサー → エクスパンダー → エグゼキューター → 出力
         ↓           ↓            ↓              ↓
      トークン列    AST       展開済みAST    実行結果
```

## 3. 主要コンポーネント

### 3.1 Shell Loop (src/shell/shell_loop.c)
- **責務**: メインループの制御、プロンプト表示、入力受付
- **主要関数**:
  - `shell_loop()`: メインループ
  - `process_input()`: 入力処理
  - `handle_line()`: 行処理

### 3.2 Lexer (src/lexer/)
- **責務**: 入力文字列をトークンに分割
- **トークン種別**:
  - WORD: 通常の単語
  - PIPE: パイプライン演算子 `|`
  - REDIR_IN: 入力リダイレクション `<`
  - REDIR_OUT: 出力リダイレクション `>`
  - REDIR_APPEND: 追記リダイレクション `>>`
  - HEREDOC: ヒアドキュメント `<<`

### 3.3 Parser (src/parser/)
- **責務**: トークン列を抽象構文木(AST)に変換
- **ノード種別**:
  - NODE_CMD: コマンドノード
  - NODE_PIPE: パイプラインノード
  - NODE_REDIR: リダイレクションノード
  - NODE_SEMICOLON: セミコロン区切りノード

### 3.4 Executor (src/executor/)
- **責務**: ASTを解釈して実行
- **主要ファイル**:
  - `execute.c`: メイン実行ロジック
  - `cmd_exec.c`, `cmd_path.c`: コマンド実行
  - `pipe.c`, `pipe_exec.c`: パイプライン処理
  - `redirect.c`: リダイレクション処理
  - `heredoc.c`, `heredoc_utils.c`: ヒアドキュメント処理
  - `assignment.c`, `assignment_utils.c`: 変数代入処理

### 3.5 Environment Manager (src/env/)
- **責務**: 環境変数の管理
- **主要ファイル**:
  - `env_init.c`: 環境変数の初期化
  - `env_list.c`: リスト操作
  - `env_utils.c`: ユーティリティ関数
  - `env_convert.c`: 配列⇔リスト変換
  - `env_dup.c`: 環境変数の複製
  - `env_export.c`: export処理

### 3.6 Signal Handler (src/signal/)
- **責務**: シグナル処理
- **主要ファイル**:
  - `signal.c`: シグナル設定
  - `signal_handler.c`: シグナルハンドラー実装
- **処理モード**:
  - MODE_INTERACTIVE (0): 対話モード
  - MODE_HEREDOC (1): ヒアドキュメント入力中
  - MODE_EXECUTING (2): コマンド実行中

### 3.7 Error Handler (src/error/)
- **責務**: エラー処理の統一管理
- **主要ファイル**:
  - `error.c`: エラーメッセージ出力
  - `error_handler.c`: エラーハンドリング
  - `error_utils.c`: エラー処理ユーティリティ

## 4. データ構造

### 4.1 主要構造体

```c
// シェル全体の状態管理
typedef struct s_shell {
    int             shell_mode;         // 現在のモード
    char            **envp;             // 環境変数配列
    t_env           *env_list;          // 環境変数リスト
    int             exit_status;        // 終了ステータス
    int             should_exit;        // 終了フラグ
    t_gnl_data      *gnl_data;          // GNLデータ
    t_gnl_data      *heredoc_gnl_data;  // ヒアドキュメント用GNLデータ
    t_input_buffer  *input_buffer;      // 入力バッファ
    int             heredoc_buffer_index; // ヒアドキュメントインデックス
    t_node          *current_ast;       // 現在のAST
    t_token         *current_tokens;    // 現在のトークン列
    char            *current_line;      // 現在の処理行
    char            *current_cmd;       // 現在のコマンド
} t_shell;

// トークン構造体
typedef struct s_token {
    int             type;       // トークン種別
    char            *value;     // トークン値
    struct s_token  *next;      // 次のトークン
} t_token;

// ASTノード構造体
typedef struct s_node {
    int             type;       // ノード種別
    union {
        t_cmd       cmd;        // コマンドデータ
        t_pipe      pipe;       // パイプデータ
        t_redir     redir;      // リダイレクションデータ
        t_semicolon semicolon;  // セミコロンデータ
    } u_data;
} t_node;

// 環境変数リスト構造体
typedef struct s_env {
    char            *key;       // 環境変数名
    char            *value;     // 環境変数値
    struct s_env    *next;      // 次のノード
} t_env;
```

## 5. メモリ管理

### 5.1 基本方針
- 動的メモリは必ず解放
- エラー時も適切にクリーンアップ
- readlineのメモリリークは許容（仕様）

### 5.2 メモリ管理関数
- `cleanup_token()`: トークンの解放
- `cleanup_ast()`: ASTの解放
- `cleanup_shell()`: シェル全体のクリーンアップ

## 6. エラーハンドリング

### 6.1 エラー種別
- 構文エラー: パース時のエラー
- 実行エラー: コマンド実行時のエラー
- システムエラー: fork/pipe等のシステムコールエラー

### 6.2 エラーコード
```c
#define ERROR_GENERAL       1
#define ERROR_BUILTIN       2
#define ERROR_FORK          254
#define ERROR_EXEC          126
#define ERROR_CMD_NOT_FOUND 127
#define ERROR_PIPE          128
```

## 7. 並行処理

### 7.1 プロセス管理
- fork()による子プロセス生成
- waitpid()による子プロセス待機
- パイプラインでの複数プロセス管理

### 7.2 ファイルディスクリプタ管理
- パイプ用FDの管理
- リダイレクション用FDの管理
- ヒアドキュメント用FDの管理

## 8. 42ノーム準拠

### 8.1 コーディング規約
- 関数: 最大25行、最大4パラメータ
- ファイル: 最大5関数
- 行幅: 最大80文字
- インデント: タブ文字使用

### 8.2 禁止事項
- for/do-while/switch文の使用禁止
- 三項演算子の使用禁止
- グローバル変数（シグナル用の1つを除く）

## 9. テスト戦略

### 9.1 ユニットテスト
- レキサーテスト: test/lexer/
- パーサーテスト: test/parser/
- ビルトインテスト: test/builtin/

### 9.2 統合テスト
- minishell_tester/
- solaldunckel-minishell-tester/

## 10. パフォーマンス考慮事項

### 10.1 最適化ポイント
- 不要なfork()の回避（ビルトインコマンド）
- 効率的な文字列処理
- 適切なバッファサイズの設定

### 10.2 制限事項
- 最大パイプライン数: 実装依存
- 最大引数数: システム制限に準拠
- 最大環境変数数: システム制限に準拠