/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:56:05 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/08 20:56:05 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"
#include <signal.h>

void	execute_redir_external(t_node *cmd, t_redir_exec *re);

t_node	*collect_redirections(t_node *cmd, t_node **redirs, int *count)
{
	t_node	*child;

	if (!cmd || cmd->type != NODE_REDIR)
		return (cmd);
	child = collect_redirections(cmd->u_data.redir.child, redirs, count);
	redirs[*count] = cmd;
	(*count)++;
	return (child);
}

int	execute_redirections(t_node **redirs, int count, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (redirect_check(redirs[i], shell) != 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	process_heredocs(t_node **redirs, int count, t_shell *shell)
{
	int	i;
	int	fd;
	int	j;

	i = -1;
	while (++i < count)
	{
		if (redirs[i]->u_data.redir.redir_type == HEREDOC)
		{
			fd = read_heredoc_to_pipe(redirs[i]->u_data.redir.filename, shell);
			if (fd < 0)
			{
				j = -1;
				while (++j < i)
					if (redirs[j]->u_data.redir.redir_type == HEREDOC
						&& redirs[j]->u_data.redir.heredoc_fd >= 0)
						close(redirs[j]->u_data.redir.heredoc_fd);
				return (-1);
			}
			redirs[i]->u_data.redir.heredoc_fd = fd;
		}
	}
	return (0);
}

static void	fork_external_cmd(t_node *cmd, t_node **redirs, int count,
		t_shell *shell)
{
	pid_t			pid;
	int				status;
	t_redir_exec	re;

	pid = fork();
	if (pid < 0)
		return (print_perror("fork"), (void)(shell->exit_status = ERROR_FORK));
	if (pid == 0)
	{
		set_child_signal_default();
		re.base_cmd = cmd;
		while (re.base_cmd && re.base_cmd->type == NODE_REDIR)
			re.base_cmd = re.base_cmd->u_data.redir.child;
		re.redirs = redirs;
		re.redir_count = count;
		re.shell = shell;
		execute_redir_external(cmd, &re);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else
		shell->exit_status = 128 + WTERMSIG(status);
}

void	execute_redir_builtin(t_node *cmd, t_shell *shell)
{
	t_node	*redirs[32];
	int		redir_count;
	t_node	*base_cmd;

	redir_count = 0;
	base_cmd = collect_redirections(cmd, redirs, &redir_count);
	if (process_heredocs(redirs, redir_count, shell) < 0)
	{
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			shell->exit_status = 130;
		}
		else
			shell->exit_status = ERROR_GENERAL;
		return ;
	}
	if (base_cmd && base_cmd->type == NODE_CMD
		&& is_builtin(base_cmd->u_data.cmd.argv[0]))
		handle_builtin_redirection(cmd, redirs, redir_count, shell);
	else
		fork_external_cmd(cmd, redirs, redir_count, shell);
}
