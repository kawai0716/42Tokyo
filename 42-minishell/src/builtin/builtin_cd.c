/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*get_target_path(char **argv, t_env *env_list)
{
	char	*target;

	if (!argv[1])
	{
		target = get_env_value(env_list, "HOME");
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (target);
	}
	else if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		target = get_env_value(env_list, "OLDPWD");
		if (!target)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putstr_fd(target, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (target);
	}
	return (argv[1]);
}

static void	update_pwd_vars(t_env **env_list, char *old_pwd, char *new_pwd)
{
	if (old_pwd)
	{
		set_env_value(env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	if (new_pwd)
	{
		set_env_value(env_list, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	builtin_cd(char **argv, t_env **env_list)
{
	char	*target;
	char	*old_pwd;
	char	*new_pwd;

	target = get_target_path(argv, *env_list);
	if (!target)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		perror("cd");
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	update_pwd_vars(env_list, old_pwd, new_pwd);
	return (0);
}
