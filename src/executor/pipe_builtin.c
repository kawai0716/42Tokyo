/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:55:42 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/21 16:55:42 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

void	handle_builtin_redirection(t_node *cmd, t_node **redirs,
	int redir_count, t_shell *shell)
{
	t_node	*base_cmd;
	int		saved_stdin;
	int		saved_stdout;

	base_cmd = collect_redirections(cmd, redirs, &redir_count);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (execute_redirections(redirs, redir_count, shell) == 0)
		execute_node(base_cmd, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
