/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 07:25:06 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 07:25:06 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

char	*get_target_path(char **argv, t_shell *shell, int *need_free);
void	update_pwd_vars(t_shell *shell, char *old_pwd, char *new_pwd);

static int	check_argc(char **argv)
{
	int	arg_count;

	arg_count = 0;
	while (argv[arg_count])
		arg_count++;
	if (arg_count > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	perform_chdir(char *target, char **old_pwd)
{
	*old_pwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
	{
		perror("cd");
		if (*old_pwd)
			free(*old_pwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*target;
	char	*old_pwd;
	char	*new_pwd;
	int		need_free;

	if (check_argc(argv) != 0)
		return (1);
	target = get_target_path(argv, shell, &need_free);
	if (!target)
		return (1);
	if (perform_chdir(target, &old_pwd) != 0)
	{
		if (need_free)
			free(target);
		return (1);
	}
	if (need_free)
		free(target);
	new_pwd = getcwd(NULL, 0);
	update_pwd_vars(shell, old_pwd, new_pwd);
	return (0);
}
