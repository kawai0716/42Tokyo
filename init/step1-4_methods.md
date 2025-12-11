# 1〜4段階で追加・整備したメソッドまとめ

- 目的: 実装済みメソッドの役割と所在を簡潔に確認するためのメモ。
- 参照: パスはリポジトリ相対。行番号は目安。

## Client
- `appendReceiveBuffer(const std::string &data)` (`src/class/Client.cpp:23` 付近)  
  `recv` で得た生データを受信バッファ `_receive_buffer` に積む。
- `extractCommand()` (`src/class/Client.cpp:29` 付近)  
  `_receive_buffer` から最初の `\r\n` までを切り出し、バッファから削除して返す。終端が無ければ空文字列。
- `sendMessage(const std::string &msg)` (`src/class/Client.cpp:63` 付近)  
  末尾に `\r\n` を補いキューへ積み、`flushSend()` で即時送信を試みる。未送信分はキューに残す。
- `hasPendingSend() const` (`src/class/Client.cpp:45` 付近)  
  `_send_buffer` に未送信データがあるか判定。
- `queueMessage(const std::string &msg)` (`src/class/Client.cpp:49` 付近)  
  メッセージを `\r\n` 付きで `_send_buffer` に追記する。
- `flushSend()` (`src/class/Client.cpp:56` 付近)  
  `_send_buffer` を `send` で可能な分だけ送信。完了で true、EAGAIN/EWOULDBLOCK で false、致命エラーでログ＋バッファクリア。

## Server
- `initSocket()` (`src/class/Server.cpp:33` 付近)  
  リッスンソケット生成、SO_REUSEADDR 設定、O_NONBLOCK 設定、bind/listen、poll への初期登録。
- `addPollFd(int fd)` (`src/class/Server.cpp:67` 付近)  
  新規クライアント FD を `POLLIN` 監視で `_pfds` に追加。
- `removePollFd(size_t index)` (`src/class/Server.cpp:74` 付近)  
  `_pfds` から指定インデックスを削除（切断時）。
- `acceptNewClient()` (`src/class/Server.cpp:92` 付近)  
  `accept` をループし、クライアント FD をノンブロッキング化して Client オブジェクトを生成、マップと poll に登録。
- `handleClientData(size_t index)` (`src/class/Server.cpp:131` 付近)  
  `recv` で読み込み、`appendReceiveBuffer` → `extractCommand` → `handleClientMessage`。`POLLHUP/POLLERR` や recv 0/エラーでクリーンアップ。
- `updatePollEvents(size_t index, short events)` (`src/class/Server.cpp:175` 付近)  
  poll エントリの events を差し替えるヘルパー（POLLIN/POLLOUT の切替用）。
- `refreshPollEvents()` (`src/class/Server.cpp:180` 付近)  
  poll 実行前に各 FD の監視ビットを再設定。送信キューがある Client は `POLLIN|POLLOUT` にする。
- `run()` (`src/class/Server.cpp:208` 付近)  
  メインループ。`refreshPollEvents` → `poll`。リッスン FD は `acceptNewClient`。クライアント FD は `POLLIN/ERR/HUP` で `handleClientData`、`POLLOUT` で `flushSend`（完了で `POLLIN` に戻す）。
- `handleClientMessage(Client *, const std::string &msg)` (`src/class/Server.cpp:241` 付近)  
  `Operation` を構築し、コマンド関数があれば実行（現状コマンド側はスタブ多数）。

## 全体の流れ（ASCIIアート）
```
Client ↔ Server 基盤（ステップ1〜4）

   acceptNewClient()
   ┌───────────┐                  ┌──────────────┐
   │  Client   │    poll(POLLIN)  │    Server    │
   │ (fd,bufs) │◀───────────────▶│ (_pfds,map)  │
   └───────────┘                  └──────────────┘
         ▲                                │
         │ recv                           │ refreshPollEvents()
         │                                │
         │ handleClientData()             │
         │  appendReceiveBuffer()         │
         │  extractCommand()  ───────────▶│ handleClientMessage()
         │                                │   Operation(cmd)
         │                                │   command(client,...)
         │                                │
         │ queueMessage() / sendMessage() │
         │ flushSend()                    │
         │ hasPendingSend()               │
         │                                │ poll で POLLOUT 検知
         │                                │ flushSend() → 完了なら POLLIN へ戻す
         │                                │
         ▼                                ▼
    送受信バッファ                 pollfd/events 更新
```
