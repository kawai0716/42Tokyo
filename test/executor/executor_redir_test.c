#include "executor.h"         // ft_split(), ft_strjoin(), ft_strdup() など libft 関数群

extern char **g_envp;  // main() から受け渡した環境変数
extern t_node *g_cmd;  // Parser で構築されたコマンドノード

void redirect_check(t_node *cmd)
{
    char *filename;
    int fd;
    if (!cmd)
        return;

    if (cmd->type == NODE_REDIR)
    {
        redirect_check(cmd->u_data.redir.child);
        filename = cmd->u_data.redir.filename;
        fd = -1;

        if(cmd->u_data.redir.redir_type == REDIR_IN)
        {
            fd = open(filename, O_RDONLY);
            if(fd < 0)
            {
                perror("open");
                return;
            }
            if(dup2(fd, STDIN_FILENO) < 0)
            {
                perror("dup2");
                return;
            }
            close(fd);

        }
        else if(cmd->u_data.redir.redir_type == REDIR_OUT)
        {
            fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd < 0)
            {
                perror("open");
                return;
            }
            if(dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2");
                return;
            }
            close(fd);
        }
        else if(cmd->u_data.redir.redir_type == REDIR_APPEND)
        {
            fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if(fd < 0)
            {
                perror("open");
                return;
            }
            if(dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2");
                return;
            }
            close(fd);
        }
        else if(cmd->u_data.redir.redir_type == HEREDOC)
        {
            // ヒアドキュメントの処理はここに追加
            // 例えば、ヒアドキュメントの内容を一時ファイルに書き込むなど
            return;
        }

        else if(cmd->type == NODE_PIPE)
        {
            // パイプの処理はここに追加
            // 例えば、パイプの左側と右側のコマンドを処理するなど
            redirect_check(cmd->u_data.pipe.left);
            redirect_check(cmd->u_data.pipe.right);
        }

        else if(cmd->type == NODE_CMD)
        {
            return;
        }
    }
}

void free_split(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char *find_cmd_path(const char *cmd)
{
    char *path_env = getenv("PATH");
    char **paths;
    char *full_path;
    char *tmp;
    int i;

    if (!path_env)
        return NULL;

    if(ft_strchr(cmd, '/'))  // コマンドにパスが含まれている場合
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);  // 実行可能ならそのまま返す
        else
            return NULL;  // 実行不可ならNULLを返す
    }
    
    paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;

    i = 0;
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(tmp, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free_split(paths);
            free(tmp);
            return full_path;
        }
        free(tmp);
        free(full_path);
        i++;
    }
    free_split(paths);
    return NULL;
}

void exec_cmd(t_node *cmd)
{
    char **argv;
    char *cmd_path;

    argv = cmd->u_data.cmd.argv;
    if (!argv || !argv[0])
    {
        printf("Error: No command to execute.\n");
        exit(EXIT_FAILURE);
    }

    cmd_path = find_cmd_path(argv[0]);
    if (!cmd_path)
    {
        printf("Error: Command not found: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (execve(cmd_path, argv, g_envp) == -1)
    {
        perror("minishell: execve");
        free(cmd_path);
        exit(EXIT_FAILURE);
    }

}

static t_node *create_redir_node(
    t_token_type redir_type,  // REDIR_IN／REDIR_OUT／REDIR_APPEND／HEREDOC のどれか
    char      *filename,      // リダイレクト先（またはヒアドキュメントの区切り文字）となる文字列
    t_node    *child          // このリダイレクトの“中身”となる子ノード（CMD ノードか、さらにネストされた REDIR ノード）
)
{
    t_node *redir = malloc(sizeof(t_node));
    if (!redir)
        return NULL;

    // 1) このノードが「リダイレクトノード」であることを示す
    redir->type = NODE_REDIR;

    // 2) どの種類のリダイレクトかを保存
    redir->u_data.redir.redir_type = redir_type;

    // 3) ファイル名（あるいはヒアドキュメントの区切り文字）を記録
    redir->u_data.redir.filename = filename;

    // 4) このリダイレクトの対象（子ノード）を紐づける
    redir->u_data.redir.child = child;

    return redir;
}

/* （2）簡易 t_node を作る関数 */
static t_node *make_test_node(void)
{
    t_node *redir_node;
    t_node *cmd_node = malloc(sizeof(t_node));
    if (!cmd_node)
        return NULL;

    cmd_node->type = NODE_CMD;

    cmd_node->u_data.cmd.argv = malloc(sizeof(char *) * 3);
    if (!cmd_node->u_data.cmd.argv)
    {
        free(cmd_node);
        return NULL;
    }
    cmd_node->u_data.cmd.argv[0] = strdup("echo");
    cmd_node->u_data.cmd.argv[1] = strdup(" sykawai");
    cmd_node->u_data.cmd.argv[2] = NULL;

    redir_node = create_redir_node(REDIR_APPEND, strdup("output.txt"),cmd_node);  // リダイレクトノードを作成（例としてNULLを使用）
    if (!redir_node)
    {
        free(cmd_node->u_data.cmd.argv[0]);
        free(cmd_node->u_data.cmd.argv[1]);
        free(cmd_node->u_data.cmd.argv);
        free(cmd_node);
        return NULL;
    }
    return redir_node;
}

/* （3）メイン関数：fork→exec_cmd→wait を行う */
int main(int argc, char **argv, char **envp)
{
    (void)argc;  // 未使用の引数を無視
    (void)argv;  // 未使用の引数を無視
    pid_t  pid;
    t_node *cmd_node;

    /* グローバル変数を設定 */
    g_envp = envp;
    g_cmd  = make_test_node();
    if (!g_cmd)
    {
        perror("make_test_node failed");
        return EXIT_FAILURE;
    }  
    // 実行するコマンドノードを取得
    cmd_node = g_cmd->u_data.redir.child;

    /* 子プロセスを作成して exec_cmd を呼び出す */
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    if (pid == 0)
    {
        /* 子プロセス */
        redirect_check(g_cmd);  // リダイレクトの設定を行う
        exec_cmd(cmd_node);  // コマンドを実行
        /* exec_cmd（execve）が失敗するとここに戻る */
        perror("exec_cmd failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* 親プロセス */
        waitpid(pid, NULL, 0);
    }

    /* メモリ解放（簡易例なので個別に free していく） */
    if (cmd_node->type == NODE_CMD) 
    {
        char **argv = cmd_node->u_data.cmd.argv;
        int i = 0;
        while (argv[i]) 
        {
            free(argv[i]);
            i++;
        }
        free(argv);
        free(cmd_node);
    }

    // 次にリダイレクトノード側の filename を解放
    free(g_cmd->u_data.redir.filename);

    // 最後にリダイレクトノード本体を解放
    free(g_cmd);

    return EXIT_SUCCESS;
}
