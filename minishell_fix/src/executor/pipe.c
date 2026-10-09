/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:56:05 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/08 20:56:05 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

static int	setup_pipeline(int fd[2], t_shell *shell)
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		shell->exit_status = ERROR_PIPE;
		return (-1);
	}
	return (0);
}

void	ex_main(t_node *cmd, t_shell *shell)
{
	t_pipe_data	pd;
	pid_t		pid1;
	pid_t		pid2;
	int			status;

	if (cmd->type != NODE_PIPE)
	{
		execute_node(cmd, shell);
		return ;
	}
	if (setup_pipeline(pd.fd, shell) == -1)
		return ;
	pd.fd_in = -1;
	pd.shell = shell;
	pid1 = create_first_child(&pd, cmd->u_data.pipe.left);
	pid2 = create_second_child(&pd, cmd->u_data.pipe.right);
	close(pd.fd[0]);
	close(pd.fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
