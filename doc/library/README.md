# Minishell 使用ライブラリ関数リファレンス

このディレクトリには、Minishellプロジェクトで使用している標準ライブラリ関数の詳細なドキュメントが含まれています。

## ドキュメント一覧

### 1. [メモリ管理関数](01_memory_management.md)
- malloc, free
- メモリ割り当てと解放

### 2. [プロセス管理関数](02_process_management.md)
- fork, execve, waitpid, exit
- プロセスの作成と制御

### 3. [ファイル操作関数](03_file_operations.md)
- open, close, read, write
- access, stat
- ファイルディスクリプタ操作

### 4. [ディレクトリ操作関数](04_directory_operations.md)
- opendir, readdir, closedir
- getcwd, chdir
- ディレクトリの走査と移動

### 5. [入出力制御関数](05_io_control.md)
- dup, dup2, pipe
- isatty
- ファイルディスクリプタのリダイレクション

### 6. [シグナル処理関数](06_signal_handling.md)
- signal, sigaction
- sigemptyset
- シグナルハンドラの設定

### 7. [Readline関数](07_readline.md)
- readline, add_history
- rl_on_new_line, rl_redisplay, rl_replace_line
- rl_clear_history
- インタラクティブ入力処理

### 8. [エラー処理関数](08_error_handling.md)
- perror
- エラーメッセージの出力

### 9. [EOF（Ctrl+D）処理](09_eof_handling.md)
- Ctrl+Dの動作原理
- readline()でのEOF処理
- ヒアドキュメントでのEOF
- インタラクティブ/非インタラクティブモードの違い

## 使用関数一覧（アルファベット順）

| 関数名 | ヘッダ | カテゴリ | 用途 |
|--------|--------|----------|------|
| access | unistd.h | ファイル操作 | ファイルのアクセス権限確認 |
| add_history | readline/history.h | Readline | コマンド履歴への追加 |
| chdir | unistd.h | ディレクトリ操作 | カレントディレクトリの変更 |
| close | unistd.h | ファイル操作 | ファイルディスクリプタのクローズ |
| closedir | dirent.h | ディレクトリ操作 | ディレクトリストリームのクローズ |
| dup | unistd.h | 入出力制御 | ファイルディスクリプタの複製 |
| dup2 | unistd.h | 入出力制御 | ファイルディスクリプタの複製と置換 |
| execve | unistd.h | プロセス管理 | プログラムの実行 |
| exit | stdlib.h | プロセス管理 | プロセスの終了 |
| fork | unistd.h | プロセス管理 | 子プロセスの作成 |
| free | stdlib.h | メモリ管理 | メモリの解放 |
| getcwd | unistd.h | ディレクトリ操作 | カレントディレクトリの取得 |
| isatty | unistd.h | 入出力制御 | 端末デバイスの判定 |
| malloc | stdlib.h | メモリ管理 | メモリの動的割り当て |
| open | fcntl.h | ファイル操作 | ファイルのオープン |
| opendir | dirent.h | ディレクトリ操作 | ディレクトリのオープン |
| perror | stdio.h | エラー処理 | エラーメッセージの出力 |
| pipe | unistd.h | 入出力制御 | パイプの作成 |
| read | unistd.h | ファイル操作 | データの読み込み |
| readdir | dirent.h | ディレクトリ操作 | ディレクトリエントリの読み込み |
| readline | readline/readline.h | Readline | 一行入力の読み込み |
| rl_clear_history | readline/history.h | Readline | 履歴のクリア |
| rl_on_new_line | readline/readline.h | Readline | 新しい行の開始を通知 |
| rl_redisplay | readline/readline.h | Readline | プロンプトの再表示 |
| rl_replace_line | readline/readline.h | Readline | 現在の行の置換 |
| sigaction | signal.h | シグナル処理 | シグナルハンドラの設定 |
| sigemptyset | signal.h | シグナル処理 | シグナルセットの初期化 |
| signal | signal.h | シグナル処理 | シグナルハンドラの設定（簡易版） |
| stat | sys/stat.h | ファイル操作 | ファイル情報の取得 |
| waitpid | sys/wait.h | プロセス管理 | 子プロセスの待機 |
| write | unistd.h | ファイル操作 | データの書き込み |

## 注意事項

### 42プロジェクトの制約
- 使用可能な関数は課題で指定されたもののみ
- libft以外の外部ライブラリは使用禁止
- グローバル変数は1つのみ（シグナル処理用）

### メモリ管理
- mallocで確保したメモリは必ずfreeする
- readlineのメモリリークは仕様上許容

### エラー処理
- システムコールの戻り値は必ずチェック
- エラー時は適切なエラーメッセージを表示

### シグナル処理
- シグナルハンドラ内では最小限の処理のみ
- シグナルセーフな関数のみ使用

## 参考資料

- [POSIX.1-2017](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [Linux man pages](https://man7.org/linux/man-pages/)
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html)