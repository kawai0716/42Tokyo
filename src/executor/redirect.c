/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 00:44:10 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/06 00:44:10 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

static int	open_redirect_file(int type, const char *filename, t_shell *shell)
{
	int	fd;

	if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HEREDOC)
		fd = read_heredoc_to_pipe(filename, shell);
	else
		fd = -1;
	return (fd);
}

static int	get_target_fd(int type)
{
	if (type == REDIR_IN || type == HEREDOC)
		return (STDIN_FILENO);
	else
		return (STDOUT_FILENO);
}

static int	get_redirect_fd(t_node *cmd, t_shell *shell)
{
	if (cmd->u_data.redir.redir_type == HEREDOC
		&& cmd->u_data.redir.heredoc_fd >= 0)
		return (cmd->u_data.redir.heredoc_fd);
	else
		return (open_redirect_file(cmd->u_data.redir.redir_type,
				cmd->u_data.redir.filename, shell));
}

int	redirect_check(t_node *cmd, t_shell *shell)
{
	int	target_fd;
	int	fd;

	if (!cmd || cmd->type != NODE_REDIR)
		return (0);
	fd = get_redirect_fd(cmd, shell);
	if (fd < 0)
	{
		perror(cmd->u_data.redir.filename);
		shell->exit_status = ERROR_GENERAL;
		return (-1);
	}
	target_fd = get_target_fd(cmd->u_data.redir.redir_type);
	if (dup2(fd, target_fd) < 0)
	{
		print_perror("dup2");
		close(fd);
		shell->exit_status = ERROR_GENERAL;
		return (-1);
	}
	if (cmd->u_data.redir.redir_type != HEREDOC
		|| cmd->u_data.redir.heredoc_fd < 0)
		close(fd);
	return (0);
}
