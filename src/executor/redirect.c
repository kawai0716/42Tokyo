/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:44:10 by marvin            #+#    #+#             */
/*   Updated: 2025/06/06 00:44:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void redirect_check(t_node *cmd)
{
    int target_fd;
    int fd;

    if (!cmd || cmd->type != NODE_REDIR)
        return;

    redirect_check(cmd->u_data.redir.child);

    const char *filename = cmd->u_data.redir.filename;
    if (cmd->u_data.redir.redir_type == REDIR_IN)
        fd = open(filename, O_RDONLY);
    else if (cmd->u_data.redir.redir_type == REDIR_OUT)
        fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    else if (cmd->u_data.redir.redir_type == REDIR_APPEND)
        fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, 0644);
    else if(cmd->u_data.redir.redir_type == HEREDOC)
        fd = read_heredoc_to_pipe(filename);

    if (fd < 0)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    target_fd = cmd->u_data.redir.redir_type == REDIR_IN;
    if(target_fd == REDIR_IN)
        target_fd = STDIN_FILENO;
    else
        target_fd = STDOUT_FILENO;

    if (dup2(fd, target_fd) < 0)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}
