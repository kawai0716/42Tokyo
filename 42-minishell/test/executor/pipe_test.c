#include "executor.h"         // ft_split(), ft_strjoin(), ft_strdup() など libft 関数群

extern char **g_envp;  // main() から受け渡した環境変数
extern t_node *g_cmd;  // Parser で構築されたコマンドノード

void run_simple_cmd(t_node *cmd)
{
    pid_t pid;
    int status;
    pid=fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        exec_cmd(cmd);
        perror("exec_cmd failed");
        exit(EXIT_FAILURE);
    }
    waitpid(pid, &status, 0);
}

void execute_node(t_node *cmd)
{
    if(cmd->type == NODE_CMD)
        run_simple_cmd(cmd);
    else if(cmd->type == NODE_REDIR)
    {
        redirect_check(cmd);
        execute_node(cmd->u_data.redir.child);  // リダイレクトの子ノードを実行 
    }
    else if(cmd->type == NODE_PIPE)
        ex_main(cmd);
}

void redirect_check(t_node *cmd)
{
    if (!cmd || cmd->type != NODE_REDIR)
        return;
    // まずは子を先に設定
    redirect_check(cmd->u_data.redir.child);

    const char *filename = cmd->u_data.redir.filename;
    int fd;
    if (cmd->u_data.redir.redir_type == REDIR_IN)
        fd = open(filename, O_RDONLY);
    else if (cmd->u_data.redir.redir_type == REDIR_OUT)
        fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    else if (cmd->u_data.redir.redir_type == REDIR_APPEND)
        fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, 0644);
    else
        return;  // HEREDOC はまだ

    if (fd < 0)
        { perror(filename); exit(EXIT_FAILURE); }

    int target_fd = (cmd->u_data.redir.redir_type == REDIR_IN)
                    ? STDIN_FILENO : STDOUT_FILENO;
    if (dup2(fd, target_fd) < 0)
        { perror("dup2"); exit(EXIT_FAILURE); }
    close(fd);
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

/* （2）簡易 t_node を作る関数 */
static t_node *make_pipe_test_node(void)
{
    t_node *left_cmd = malloc(sizeof(t_node));
    t_node *right_cmd = malloc(sizeof(t_node));
    t_node *pipe_node;
    if (!left_cmd || !right_cmd)
        return NULL;

    /* 左側: ls -l */
    left_cmd->type = NODE_CMD;
    left_cmd->u_data.cmd.argv = malloc(sizeof(char *) * 3);
    left_cmd->u_data.cmd.argv[0] = strdup("ls");
    left_cmd->u_data.cmd.argv[1] = strdup("-l");
    left_cmd->u_data.cmd.argv[2] = NULL;

    /* 右側: grep pipe */
    right_cmd->type = NODE_CMD;
    right_cmd->u_data.cmd.argv = malloc(sizeof(char *) * 3);
    right_cmd->u_data.cmd.argv[0] = strdup("grep");
    right_cmd->u_data.cmd.argv[1] = strdup("pipe");
    right_cmd->u_data.cmd.argv[2] = NULL;

    /* パイプノードを組み立て */
    pipe_node = malloc(sizeof(t_node));
    if (!pipe_node)
        return NULL;
    pipe_node->type = NODE_PIPE;
    pipe_node->u_data.pipe.left  = left_cmd;
    pipe_node->u_data.pipe.right = right_cmd;

    return pipe_node;
}

// 再帰的に t_node を free する簡易実装
void free_node(t_node *node)
{
    if (!node) return;
    if (node->type == NODE_REDIR)
    {
        free_node(node->u_data.redir.child);
        free(node->u_data.redir.filename);
    }
    else if (node->type == NODE_PIPE)
    {
        free_node(node->u_data.pipe.left);
        free_node(node->u_data.pipe.right);
    }
    else if (node->type == NODE_CMD)
    {
        char **argv = node->u_data.cmd.argv;
        for (int i = 0; argv && argv[i]; i++)
            free(argv[i]);
        free(argv);
    }
    free(node);
}


void ex_main(t_node *g_cmd)
{
    int fd[2];
    pid_t pid_left;
    pid_t pid_right;
    t_node *left;
    t_node *right;
    int status;

    left = g_cmd->u_data.pipe.left;
    right = g_cmd->u_data.pipe.right;
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_left = fork();
    if (pid_left < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid_left == 0)
    {
        // Child process
        close(fd[0]);  // Close read end of pipe
        dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(fd[1]);  // Close write end of pipe
        execute_node(left);  // パイプの左側のコマンドを処理
        exit(EXIT_FAILURE);
    }

    pid_right = fork();
    if (pid_right < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid_right == 0)
    {
        // Child process
        close(fd[1]);  // Close write end of pipe
        dup2(fd[0], STDIN_FILENO);  // Redirect stdin to pipe
        close(fd[0]);  // Close read end of pipe
        execute_node(right);  // パイプの右側のコマンドを処理
        exit(EXIT_FAILURE);
    }
    close(fd[0]);  // Close read end of pipe in parent
    close(fd[1]);  // Close write end of pipe in parent
    waitpid(pid_left, &status, 0);
    waitpid(pid_right, &status, 0);
}

/* （3）メイン関数：fork→exec_cmd→wait を行う */
int main(int argc, char **argv, char **envp)
{
    (void)argc; (void)argv;
    g_envp = envp;
    g_cmd  = make_pipe_test_node();
    if (!g_cmd) { perror("make_pipe_test_node"); return EXIT_FAILURE; }
    execute_node(g_cmd);
    free_node(g_cmd);
    return EXIT_SUCCESS;
}
