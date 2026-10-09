/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:56:05 by marvin            #+#    #+#             */
/*   Updated: 2025/06/08 20:56:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
        execute_node(cmd->u_data.redir.child);
    }
    else if(cmd->type == NODE_PIPE)
        ex_main(cmd);
}