/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:08:49 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 01:08:49 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (1);
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(argv, shell));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd(shell));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(argv, shell));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(argv, shell));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env(shell));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit(argv, shell));
	return (1);
}
