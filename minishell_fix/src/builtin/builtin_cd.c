/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:28:40 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 14:28:40 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static char	*get_home_path(t_env *env_list)
{
	char	*target;

	target = get_env_value(env_list, "HOME");
	if (!target)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (target);
}

static char	*get_oldpwd_path(t_env *env_list)
{
	char	*target;

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

static char	*expand_tilde(const char *arg, t_env *env_list,
		int *need_free)
{
	char	*home;
	char	*expanded;

	home = get_home_path(env_list);
	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		return (home);
	expanded = ft_strjoin(home, arg + 1);
	if (!expanded)
		return (NULL);
	*need_free = 1;
	return (expanded);
}

char	*get_target_path(char **argv, t_shell *shell, int *need_free)
{
	*need_free = 0;
	if (!argv[1])
		return (get_home_path(shell->env_list));
	if (argv[1][0] == '~' && (argv[1][1] == '\0'
			|| argv[1][1] == '/'))
		return (expand_tilde(argv[1], shell->env_list, need_free));
	if (ft_strncmp(argv[1], "-", 2) == 0)
		return (get_oldpwd_path(shell->env_list));
	return (argv[1]);
}


void	update_pwd_vars(t_shell *shell, char *old_pwd, char *new_pwd)
{
	if (old_pwd)
	{
		set_env_value(&shell->env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	if (new_pwd)
	{
		set_env_value(&shell->env_list, "PWD", new_pwd);
		free(new_pwd);
	}
}
