/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:56:05 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/08 20:56:05 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

int	handle_cmd_not_found(char *cmd_name, t_shell *shell)
{
	print_error_with_arg(NULL, cmd_name, "command not found");
	shell->exit_status = ERROR_COMMAND_NOT_FOUND;
	return (0);
}

int	check_path_errors(char *cmd_path, char *cmd_name, t_shell *shell)
{
	if (ft_strcmp(cmd_path, "permission_denied") == 0)
	{
		print_error_with_arg(NULL, cmd_name, "Permission denied");
		shell->exit_status = 126;
		return (0);
	}
	if (ft_strcmp(cmd_path, "is_directory") == 0)
	{
		print_error_with_arg(NULL, cmd_name, "Is a directory");
		shell->exit_status = 126;
		return (0);
	}
	if (ft_strcmp(cmd_path, "no_such_file") == 0)
	{
		print_error_with_arg(NULL, cmd_name, "No such file or directory");
		shell->exit_status = ERROR_COMMAND_NOT_FOUND;
		return (0);
	}
	return (1);
}

int	has_control_chars(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] > 0 && str[i] < 32 && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	handle_assignment_result(int result, char ***new_argv, t_shell *shell)
{
	(void)new_argv;
	if (result == -1)
	{
		shell->exit_status = ERROR_GENERAL;
		return (0);
	}
	if (result == 0)
	{
		shell->exit_status = 0;
		return (0);
	}
	return (1);
}
