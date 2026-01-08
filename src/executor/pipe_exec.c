/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:32:44 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/21 16:32:44 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

void	execute_redir_external(t_node *cmd, t_redir_exec *re)
{
	int		i;

	(void)cmd;
	i = 0;
	while (i < re->redir_count)
	{
		if (redirect_check(re->redirs[i], re->shell) == -1)
		{
			re->shell->exit_status = ERROR_GENERAL;
			exit(ERROR_GENERAL);
		}
		i++;
	}
	exec_cmd(re->base_cmd, re->shell);
}

pid_t	create_first_child(t_pipe_data *pd, t_node *left)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		exit(ERROR_FORK);
	if (pid == 0)
	{
		set_child_signal_default();
		close(pd->fd[0]);
		dup2(pd->fd[1], STDOUT_FILENO);
		close(pd->fd[1]);
		if (pd->fd_in != -1)
		{
			dup2(pd->fd_in, STDIN_FILENO);
			close(pd->fd_in);
		}
		execute_node(left, pd->shell);
		exit_status = pd->shell->exit_status;
		cleanup_shell_for_exec(pd->shell);
		free(pd->shell);
		exit(exit_status);
	}
	return (pid);
}

pid_t	create_second_child(t_pipe_data *pd, t_node *right)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		exit(ERROR_FORK);
	if (pid == 0)
	{
		set_child_signal_default();
		close(pd->fd[1]);
		dup2(pd->fd[0], STDIN_FILENO);
		close(pd->fd[0]);
		execute_node(right, pd->shell);
		exit_status = pd->shell->exit_status;
		cleanup_shell_for_exec(pd->shell);
		free(pd->shell);
		exit(exit_status);
	}
	return (pid);
}

void	pipeline_child(t_pipe_data *pd)
{
	int	exit_status;

	set_child_signal_default();
	close(pd->fd[0]);
	if (pd->fd_in != -1)
	{
		dup2(pd->fd_in, STDIN_FILENO);
		close(pd->fd_in);
	}
	dup2(pd->fd[1], STDOUT_FILENO);
	close(pd->fd[1]);
	execute_node(pd->cmd, pd->shell);
	exit_status = pd->shell->exit_status;
	cleanup_shell_for_exec(pd->shell);
	free(pd->shell);
	exit(exit_status);
}
