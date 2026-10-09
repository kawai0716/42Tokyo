/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:49 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/31 19:06:49 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

void	exec_cmd(t_node *cmd, t_shell *shell)
{
	char	**envp;
	char	*cmd_path;

	envp = env_list_to_array(shell->env_list);
	if (!envp)
		handle_env_error(shell);
	cmd_path = find_cmd_path(cmd->u_data.cmd.argv[0], shell);
	if (!cmd_path)
		handle_cmd_not_found_exec(envp, cmd->u_data.cmd.argv[0], shell);
	execve(cmd_path, cmd->u_data.cmd.argv, envp);
	perror("execve");
	free(cmd_path);
	free_split(envp);
	cleanup_shell_for_exec(shell);
	free(shell);
	exit(ERROR_EXEC);
}
