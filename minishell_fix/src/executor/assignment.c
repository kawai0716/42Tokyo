/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:22:57 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/05 17:22:57 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "libft.h"

int	count_non_assignments(char **argv, int start_idx);
int	has_assignment(char **argv);
int	create_cmd_argv(char **argv, char ***new_argv, int start_idx, int count);

static int	handle_assignment(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (0);
	key = ft_strndup(arg, equal_pos - arg);
	if (!key)
		return (-1);
	value = ft_strdup(equal_pos + 1);
	if (!value)
	{
		free(key);
		return (-1);
	}
	set_env_value(&shell->env_list, key, value);
	free(key);
	free(value);
	return (1);
}

static int	process_only_assignments(char **argv, t_shell *shell)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (handle_assignment(argv[i], shell) == -1)
			return (-1);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}

int	create_cmd_argv(char **argv, char ***new_argv, int start_idx, int count)
{
	int	i;
	int	j;

	*new_argv = malloc(sizeof(char *) * (count + 1));
	if (!*new_argv)
		return (-1);
	i = start_idx;
	j = 0;
	while (argv[i])
	{
		(*new_argv)[j] = argv[i];
		i++;
		j++;
	}
	(*new_argv)[j] = NULL;
	return (0);
}

int	process_assignments(char **argv, char ***new_argv, t_shell *shell)
{
	int	i;
	int	cmd_start;
	int	non_assign_count;

	i = 0;
	cmd_start = -1;
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '='))
		{
			cmd_start = i;
			break ;
		}
		if (handle_assignment(argv[i], shell) == -1)
			return (-1);
		i++;
	}
	if (cmd_start == -1)
		return (process_only_assignments(argv, shell));
	non_assign_count = count_non_assignments(argv, cmd_start);
	if (create_cmd_argv(argv, new_argv, cmd_start, non_assign_count) == -1)
		return (-1);
	return (1);
}
