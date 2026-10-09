/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/28 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

void	handle_env_error(t_shell *shell)
{
	perror("env_list_to_array");
	cleanup_shell_for_exec(shell);
	free(shell);
	exit(ERROR_GENERAL);
}

void	handle_cmd_not_found_exec(char **envp, char *cmd_name, t_shell *shell)
{
	print_error_with_arg(NULL, cmd_name, "command not found");
	free_split(envp);
	cleanup_shell_for_exec(shell);
	free(shell);
	exit(ERROR_COMMAND_NOT_FOUND);
}
