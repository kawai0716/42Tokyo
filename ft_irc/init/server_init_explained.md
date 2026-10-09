# ソケット初期化の解説（Server / main）



## Serverクラスの初期化手順（`src/class/Server.cpp`/`.hpp`）
1. `Server(int port, const std::string &password)`  
   - ポートとパスワードを保持し、`initSocket()`を呼んでリッスンFDを作成。失敗時は例外を送出。
2. `initSocket()`の中身  
   - `socket(AF_INET, SOCK_STREAM, 0)`  
     - IPv4/TCPソケットを作成。失敗: `socket() failed: <errno>`。
   - `setsockopt(SO_REUSEADDR)`  
     - TIME_WAITでポートが塞がっていても再利用しやすくする。失敗: `setsockopt() failed: <errno>`。
   - `fcntl(F_SETFL, O_NONBLOCK)`  
     - ソケットをノンブロッキング化。`poll`で複数FDを扱うための準備。失敗: `fcntl() failed: <errno>`。
   - `bind(INADDR_ANY, port)`  
     - 指定ポートに割り当て。ポート使用中などで失敗: `bind() failed: <errno>`。
   - `listen(SOMAXCONN)`  
     - 接続待ち受け開始。失敗: `listen() failed: <errno>`。
   - `poll`登録  
     - `_pfds`に`listen_fd`を`POLLIN`で追加し、後続の`poll`監視に備える。
3. エラー処理  
   - どの段階で失敗しても`close(_listen_fd)`した上で`std::runtime_error`を投げ、`strerror(errno)`付きのメッセージを返す。
4. アクセサ  
   - `getListenFd()`でリッスンFD、`getPollFds()`で監視FD一覧を参照（現時点ではループ未実装）。

## poll監視リスト `_pfds` の役割
- `std::vector<struct pollfd> _pfds;` は `poll()` に渡す監視対象のFDリスト。  
  - `pollfd.fd` : 監視したいソケット（リッスンFDやクライアントFD）。  
  - `pollfd.events` : 監視するイベント種別。現状は `POLLIN`（読み込み可能）をセット。  
  - `pollfd.revents` : `poll` 呼び出し後に実際に起きたイベントが格納される。  
- `poll` にこの配列を渡して「どのFDに読み込み/書き込み等のイベントが来たか」を判定するために使用する。`Server` はここでリッスンFDおよびクライアントFDを管理する予定。

## コピー・デフォルトをprivateに置いている理由、生成を禁止している理由
- 宣言だけの `Server(); Server(const Server &); Server &operator=(const Server &);` を private に置くことで、意図しない生成/コピーを防ぐ（C++98では `= delete` が使えないための定番手法）。  
  - デフォルト構築を禁止: ポート/パスワード未設定のサーバーは意味がない。`Server(int port, const std::string &password)` のみを使わせる。  
  - コピー/代入を禁止: ソケットFDなどのリソースをコピーすると「複数インスタンスが同じFDを閉じる」などの事故を防ぎたい。  
- 公開するのは「ポートとパスワードを受け取るコンストラクタ」のみ、それ以外の生成経路は封じる設計。

## mainの起動フロー（`src/main.cpp`）
1. 引数チェック  
   - `<port> <password>`の2つを要求。足りなければ`Usage: ...`で終了。
2. ポート検証  
   - `strtol`で数値化し1〜65535の範囲内か確認。範囲外/非数値なら`Invalid port`で終了。
3. サーバー生成  
   - `Server server(port, argv[2]);`でソケット初期化が実行される（上記手順）。
4. 成功表示  
   - 初期化が通ったポートとリッスンFD番号を表示して終了（現状はループ未実装）。

## 次の実装予定
- `poll`ループと`accept/recv`のスケルトンを追加し、`_pfds`や`getListenFd()`を活用する。
- クライアント管理・バッファ処理を組み合わせて、Operationに渡す流れを作る。
