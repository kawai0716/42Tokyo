# Export識別子検証バグ修正
日時: 2025-07-20

## 問題の概要
コミット 15a8c9e (fix norm) でsolaldunckel-testerが失敗するようになった。
失敗テスト: `export TE+S=T=""`

## 原因
`is_valid_identifier`関数が`builtin_export.c`から`builtin_export2.c`に移動された際、識別子検証ロジックが誤って変更された。

### 変更前（正しいロジック）
```c
while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
```

### 変更後（バグのあるロジック）
```c
while (str[i] && str[i] != '=' && str[i] != '+')
```

## 影響
- `export TE+S=T=""`のような無効な識別子がエラーとして検出されない
- bashでは`export: 'TE+S=T=': not a valid identifier`というエラーを出力すべき
- minishellは何もエラーを出さずに環境変数を表示してしまう

## 修正内容
`src/builtin/builtin_export2.c`の`is_valid_identifier`関数を元の正しいロジックに戻した。
これにより`+=`演算子の正しい検証が行われるようになり、`+`の後に`=`が続かない場合は無効な識別子として正しくエラーが報告される。

## テスト結果
修正後、solaldunckel-testerの全テストが通過（0失敗）