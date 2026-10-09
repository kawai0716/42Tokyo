/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 10:39:57 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 10:39:57 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	builtin_pwd(t_shell *shell)
{
	char	*cwd;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		pwd_env = get_env_value(shell->env_list, "PWD");
		if (pwd_env)
		{
			ft_putstr_fd(pwd_env, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			return (0);
		}
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	return (0);
}
