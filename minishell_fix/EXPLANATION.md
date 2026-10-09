  Compile

  - make -n 実行されるビルドコマンドの表示（実行しない）
  - make 通常ビルド
  - make 再実行して不要な再リンクが起きないか確認

  Simple command and globals

  - /bin/ls 絶対パスの単純コマンド実行
  - <Enter> 空入力が無視されるか
  - <Space><Enter> 空白のみ入力が無視されるか
  - <Tab><Enter> タブのみ入力が無視されるか
  - グローバル変数は「受信シグナル番号のみ」保持しているか確認

  Arguments

  - /bin/ls -a 引数処理（隠しファイル）
  - /bin/ls -l . 引数とカレント指定の処理
  - /bin/echo hello world 引数の分割と渡し
  - /bin/pwd -L 引数付き実行

  echo

  - echo 空引数出力（改行だけ）
  - echo hello 通常出力
  - echo -n hello -n で改行を抑止
  - echo -n hello world 複数引数の連結表示

  exit

  - exit 通常終了
  - exit 0 終了コード 0
  - exit 42 終了コード 42
  - exit 1 2 引数過多のエラー処理

  Return value

  - /bin/ls 成功コマンド
  - echo $? 直前の終了コード表示
  - /bin/ls filethatdoesntexist 失敗コマンド
  - echo $? 失敗の終了コード確認
  - nosuchcmd コマンド未発見
  - echo $? 未発見の終了コード確認
  - echo $? $? 2回展開されるか
  - echo $?$? 文字列結合の展開を確認

  Signals

  - 空プロンプトで Ctrl‑C/Ctrl‑\ /Ctrl‑D の挙動確認
  - 入力途中での Ctrl‑C/Ctrl‑\ /Ctrl‑D の挙動確認
  - cat 実行中に Ctrl‑C/Ctrl‑\ /Ctrl‑D の挙動確認

  Double quotes

  - echo "hello world" 空白を含む引数保持
  - echo "cat lol.c | cat > lol.c" メタ文字が解釈されない
  - echo "  spaced   out " 連続空白の保持
  - echo "mix $USER and text" 変数展開が有効

  Single quotes

  - echo 'hello world' 空白を含む引数保持
  - echo '' 空文字引数
  - echo '$USER' 変数展開されない
  - echo 'a | b > c < d' メタ文字をそのまま
  - echo '   spaced   ' 連続空白の保持

  env

  - env 環境変数一覧が出るか

  export

  - export TEST=hello 新規作成
  - env | grep TEST 反映確認
  - export TEST=world 上書き
  - export NEWVAR= 空値の作成
  - export A=1 / export Z=1 ソート順確認
  - export 一覧表示の形式確認

  unset

  - unset TEST 変数削除
  - env | grep TEST 削除確認
  - unset PATH PATH 削除
  - env | grep PATH 削除確認

  cd

  - pwd 現在地確認
  - cd / / cd .. / cd . 基本移動
  - cd ~ HOME への移動
  - cd nosuchdir 失敗時のエラー処理

  pwd

  - pwd どの場所でも正しいパスが出るか

  Relative path

  - ../minishell 相対パスの実行
  - ./minishell カレントからの実行
  - .././../bin/ls 複雑な相対パス解決

  Environment PATH

  - ls PATH 経由の実行
  - unset PATH で PATH 無効化
  - ls 実行不可になるか
  - export PATH=/bin:/usr/bin PATH 設定
  - ls 復旧するか

  PATH順序確認:

  - /tmp/ms1 /tmp/ms2 に同名コマンド作成 → PATH の左優先を確認

  Redirection

  - echo hello > out.txt 出力リダイレクト
  - cat < out.txt 入力リダイレクト
  - echo world >> out.txt 追記
  - echo hi > out1.txt > out2.txt 複数リダイレクトの優先
  - cat < nosuchfile 入力失敗時のエラー
  - cat << EOF ... EOF heredoc の処理

  Pipes

  - cat file | grep bla | wc -l 多段パイプ
  - ls filethatdoesntexist | grep bla | wc -l パイプ内エラーの扱い
  - echo hello | cat | cat 単純な多段連結
  - echo hello > out.txt | cat リダイレクトとパイプの優先
  - cat < out.txt | grep he 入力リダイレクト＋パイプ

  History and robustness

  - Up/Down キーで履歴移動
  - dsbksdgbksdghsd 未知コマンドのエラー処理
  - cat | cat | ls 変な構成でもクラッシュしない
  - 長い引数列で安定動作するか

  Environment variables

  - echo $USER 変数展開
  - echo "$USER" ダブルクオート内展開
  - echo "$USER test" 混在展開
  - export USER=alice 変数更新
  - echo "$USER" 反映確認

  Bonus: And/Or

  - /bin/false && echo ok 失敗時に実行されない
  - /bin/false || echo ok 失敗時に実行される
  - /bin/true && echo ok 成功時に実行される
  - /bin/true || echo ok 成功時に実行されない
  - ( /bin/false || echo ok ) サブシェルの論理演算
  - ( /bin/true && echo ok ) サブシェルの論理演算

  Bonus: Wildcard

  - echo * ワイルドカード展開
  - echo *.c 拡張子フィルタ
  - ls *.h マッチがない時の挙動確認

  Bonus: Surprise

  - export USER=alice 変数設定
  - echo "'$USER'" シングルクオートは文字として出る
  - echo '"$USER"' ダブルクオートは文字として出る

  必要なら、この説明をそのまま README に書き起こせる形に整形します。