/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:49 by marvin            #+#    #+#             */
/*   Updated: 2025/05/31 19:06:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

extern char **g_envp;
extern t_node *g_cmd;

char *find_cmd_path(const char *cmd)
{
    char *path_env = getenv("PATH");
    char **paths;
    char *full_path;
    int i;

    if (!path_env)
        return NULL;

    if(ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        else
            return NULL;
    }
    
    paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;

    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free_split(paths);
            return full_path;
        }
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
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execute_node(left);
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
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execute_node(right);
        exit(EXIT_FAILURE);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid_left, &status, 0);
    waitpid(pid_right, &status, 0);
}
