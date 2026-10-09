/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:22:57 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/05 17:22:57 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtin.h"
#include "libft.h"

int		count_non_assignments(char **argv, int start_idx);
char	**create_new_argv(char **argv, int start_idx, int count);

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_assignment(const char *str)
{
	char	*eq_pos;
	char	*var_name;
	int		is_valid;

	if (!str)
		return (0);
	eq_pos = ft_strchr(str, '=');
	if (!eq_pos || eq_pos == str)
		return (0);
	var_name = ft_substr(str, 0, eq_pos - str);
	if (!var_name)
		return (0);
	is_valid = is_valid_identifier(var_name);
	free(var_name);
	return (is_valid);
}

int	process_assignment(const char *str, t_shell *shell)
{
	char	*eq_pos;
	char	*var_name;
	char	*value;
	int		result;

	eq_pos = ft_strchr(str, '=');
	if (!eq_pos)
		return (1);
	var_name = ft_substr(str, 0, eq_pos - str);
	if (!var_name)
		return (1);
	value = eq_pos + 1;
	set_env_value(&shell->env_list, var_name, value);
	result = 0;
	free(var_name);
	return (result);
}

int	count_non_assignments(char **argv, int start_idx)
{
	int	count;
	int	i;

	count = 0;
	i = start_idx;
	while (argv[i])
	{
		count++;
		i++;
	}
	return (count);
}

char	**create_new_argv(char **argv, int start_idx, int count)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = start_idx;
	j = 0;
	while (argv[i])
	{
		result[j] = argv[i];
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}
