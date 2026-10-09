# フェーズ2 追加コードまとめ（pollループ/クライアント管理）

## Server の主要メソッド
- 🟢 `run()` (`src/class/Server.cpp`): `poll` で FD を監視し、リッスン FD なら `acceptNewClient()`, それ以外はインデックスを渡して `handleClientData()` を呼ぶメインループ。
- 🟦 `addPollFd(int fd)`: `acceptNewClient()` で受け入れたクライアント FD を `_pfds` に追加し、`POLLIN` で読み込みイベントを待つ。
- 🟧 `removePollFd(size_t index)`: 切断やエラー時に `_pfds` から該当エントリを削除し、監視対象から外す。
- 🟩 `acceptNewClient()`: リスニングソケットに接続が来たら `accept` を回し、ノンブロッキング設定を行い `Client` を生成して `_clients` と `_pfds` に登録する。新規接続受け入れの入口。
- 🟥 `handleClientData(size_t index)`: `_pfds` 指定インデックスのクライアント FD から `recv` で読み込み、`Client` の受信バッファに積み、区切られたコマンドを `handleClientMessage()` へ渡す。`recv` の 0/エラーや `POLLHUP/POLLERR` 時はクライアントをクローズし `_clients` から削除して `removePollFd()`。

## Client のメソッド（set 以外）
- 🟢 `Client(int fd)` (`src/class/Client.cpp:12`): ソケット FD を保持し、ニックネーム/ユーザー名を空、認証/登録フラグを false、受信バッファを空で初期化。
- 🟦 `getFd()`, `getNickname()`, `isAuthenticated()` (`src/class/Client.cpp:19-21`): それぞれ FD、現在のニックネーム、認証済みかどうかを返す（登録フラグのゲッターは未実装）。
- 🟨 `appendReceiveBuffer(const std::string &data)` (`src/class/Client.cpp:27`): `recv` で得た生データを受信バッファ末尾に積み、`\r\n` が揃うまで保持。
- 🟪 `extractCommand()` (`src/class/Client.cpp:32`): 受信バッファから最初の `\r\n` までを 1 コマンドとして切り出し、バッファから削除して返す。終端が無ければ空文字列を返す。
- 🟥 `sendMessage(const std::string &msg)` (`src/class/Client.cpp:41`): 末尾に `\r\n` が無ければ付け足して `send`。ノンブロッキングで送れなかった分は現状キューせず破棄し、エラーは標準エラーに記録。
