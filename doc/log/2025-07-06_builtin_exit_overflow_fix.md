# builtin_exit Overflow Detection Fix
Date: 2025-07-06

## 問題
`builtin_exit`コマンドで、LONG_MAX/LONG_MIN境界値を超える数値に対して適切なエラー処理が行われていなかった。

失敗していたテストケース:
- `exit 9223372036854775808` - LONG_MAX + 1
- `exit -9223372036854775810` - LONG_MIN - 2

期待される動作: "numeric argument required"エラーを表示し、終了コード2で終了

## 解決策
`builtin_exit.c`に以下の改修を実施:

1. **カスタムatol関数の実装** (`custom_atol`)
   - オーバーフロー検出機能付き
   - LONG_MAX/LONG_MIN境界値の適切な処理

2. **オーバーフロー検出関数** (`check_overflow`)
   - 次の桁を追加する前にオーバーフローを事前検出
   - 符号（正/負）に応じた適切な境界値チェック

3. **builtin_exit関数の修正**
   - `ft_atoi`の代わりに`custom_atol`を使用
   - オーバーフロー時は"numeric argument required"エラーを表示

## テスト結果
- `exit 9223372036854775808` → "numeric argument required" ✓
- `exit -9223372036854775810` → "numeric argument required" ✓
- `exit 9223372036854775807` (LONG_MAX) → 正常動作 ✓
- `exit -9223372036854775808` (LONG_MIN) → 正常動作 ✓
- `exit 99999999999999999999999` → "numeric argument required" ✓

## 変更ファイル
- `src/builtin/builtin_exit.c`

## 技術的詳細
オーバーフロー検出のアルゴリズム:
- 現在の結果値が`LONG_MAX / 10`を超える場合、次の桁を追加するとオーバーフロー
- 現在の結果値が`LONG_MAX / 10`と等しい場合、次の桁が`LONG_MAX % 10`を超えるとオーバーフロー
- 負の数の場合も同様の処理（LONG_MINに対して）