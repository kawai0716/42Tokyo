# 2025-07-21 t_pipe_data 構造体へのリファクタリング

## 概要
pipeline_child、create_first_child、create_second_child関数の呼び出しを新しいt_pipe_data構造体を使用するように更新しました。

## 変更内容

### 1. 削除されたファイル
- `/src/executor/ex_pipeline.c` - 古い関数実装が新しい実装と競合していたため削除

### 2. 修正されたファイル

#### `/src/executor/ex_main2.c`
- `ex_main()`関数を新しいt_pipe_data構造体を使用するように更新
- 古い関数宣言を削除
- `wait_for_children()`関数を削除（不要になったため）

変更前:
```c
pid1 = create_first_child(fd, cmd, shell);
pid2 = create_second_child(fd, cmd, pid1, shell);
```

変更後:
```c
t_pipe_data pd;
pd.fd_in = -1;
pd.shell = shell;
create_first_child(&pd, cmd->u_data.pipe.left);
create_second_child(&pd, cmd->u_data.pipe.right);
```

#### `/src/executor/heredoc2.c`
- 重複したt_heredoc構造体定義を削除（executor.hで既に定義済み）

#### `/src/executor/pipe2.c`
- 古い`execute_redir_external`関数の宣言と実装を削除
- 新しい`execute_redir_external`関数の宣言を追加
- `is_builtin_cmd`を`is_builtin`に修正

#### `/src/executor/pipe4.c`
- 未使用パラメータの警告を修正（`(void)cmd;`を追加）

#### `/includes/executor.h`
- `is_builtin_cmd`を`is_builtin`に修正（実装と一致させるため）

## 新しい関数シグネチャ

### 変更前
```c
void pipeline_child(int fd[2], int fd_in, t_node *cmd, t_shell *shell);
int create_first_child(int fd[2], t_node *cmd, t_shell *shell);
int create_second_child(int fd[2], t_node *cmd, pid_t pid1, t_shell *shell);
```

### 変更後
```c
void pipeline_child(t_pipe_data *pd);
void create_first_child(t_pipe_data *pd, t_node *left);
void create_second_child(t_pipe_data *pd, t_node *right);
```

## t_pipe_data構造体
```c
typedef struct s_pipe_data
{
    int     fd[2];
    int     fd_in;
    t_node  *cmd;
    t_shell *shell;
}   t_pipe_data;
```

## 結果
- コンパイルエラーはすべて解決
- パイプライン関連の関数呼び出しがすべて新しい構造体を使用するように統一された
- コードの可読性と保守性が向上