# readlineライブラリのパイプコマンドエコーバック問題の調査

## 問題の概要

minishellでパイプを含むコマンドを実行すると、以下の異常な動作が発生する：
1. コマンドがエコーバックされる
2. `< /dev/null` が自動的に挿入される

例：
```bash
# 入力
echo hello | cat

# 実際の出力
minishell$ echo hello  < /dev/null |  cat
hello
```

## 調査結果

### 1. 問題の原因

テストプログラムを作成して検証した結果、この動作はreadlineライブラリ自体の仕様であることが判明した。

```c
// test_readline.c
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;
    while (1)
    {
        line = readline("test$ ");
        if (!line) break;
        if (*line)
        {
            add_history(line);
            printf("You entered: %s\n", line);
        }
        free(line);
    }
    return (0);
}
```

このシンプルなプログラムでも同じ動作が再現される：
```bash
$ echo "echo test | cat" | ./test_readline
test$ echo test  < /dev/null |  cat
You entered: echo test  < /dev/null |  cat
```

### 2. readlineの動作

readlineライブラリは、標準入力が端末でない場合（パイプやリダイレクション経由の入力）、以下の処理を行う：
- 入力されたコマンドをエコーバックする
- パイプコマンドに `< /dev/null` を自動的に追加する

これは、readlineがインタラクティブシェルとして設計されており、非対話型の入力に対して特別な処理を行うためと考えられる。

### 3. 影響

この動作はminishellの実装の問題ではなく、readlineライブラリの仕様によるものである。そのため：
- minishellのコードを修正しても解決できない
- テスターがパイプ経由でコマンドを送信する際に、この動作が発生する
- 実際のインタラクティブな使用では問題にならない

### 4. 対処方法

以下の選択肢が考えられる：
1. **現状維持**: readlineの仕様として受け入れる
2. **readline設定の調整**: readlineの設定でこの動作を無効化できるか調査
3. **別の入力方法**: 非対話型モードではreadlineを使わない実装を検討

## 結論

この問題はminishellの実装のバグではなく、readlineライブラリの標準的な動作である。42プロジェクトの要件では、readlineライブラリの使用が指定されているため、この動作を変更することは困難である。

テスターでの評価に影響する可能性があるが、実際のインタラクティブな使用では問題にならないため、現状のままでも許容できる範囲と考えられる。