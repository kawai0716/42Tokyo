/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:05:03 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 11:05:03 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static void	export_with_append(char *arg, t_shell *shell, char *plus_sign);
int			is_valid_identifier(char *str);

static size_t	env_list_size(t_env *env_list)
{
	size_t	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static int	compare_env_key(const char *a, const char *b)
{
	return (ft_strncmp(a, b, ft_strlen(a) + 1));
}

static void	sort_env_array(t_env **array, size_t count)
{
	size_t	i;
	size_t	j;
	t_env	*tmp;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (compare_env_key(array[i]->key, array[j]->key) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_env(t_env *env_list)
{
	t_env	**array;
	size_t	count;
	size_t	i;

	count = env_list_size(env_list);
	if (count == 0)
		return ;
	array = malloc(sizeof(t_env *) * count);
	if (!array)
		return ;
	i = 0;
	while (env_list)
	{
		array[i++] = env_list;
		env_list = env_list->next;
	}
	sort_env_array(array, count);
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(array[i]->key, STDOUT_FILENO);
		if (array[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(array[i]->value, STDOUT_FILENO);
			ft_putchar_fd('\"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	free(array);
}


static void	export_with_value(char *arg, t_shell *shell, char *equal_sign)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	set_env_value(&shell->env_list, key, value);
	free(key);
	free(value);
}

static void	export_with_append(char *arg, t_shell *shell, char *plus_sign)
{
	char	*key;
	char	*new_value;
	char	*current_value;
	char	*appended_value;

	key = ft_substr(arg, 0, plus_sign - arg);
	new_value = ft_strdup(plus_sign + 2);
	current_value = get_env_value(shell->env_list, key);
	if (current_value)
	{
		appended_value = ft_strjoin(current_value, new_value);
		set_env_value(&shell->env_list, key, appended_value);
		free(appended_value);
	}
	else
		set_env_value(&shell->env_list, key, new_value);
	free(key);
	free(new_value);
}

static int	export_var(char *arg, t_shell *shell)
{
	char	*equal_sign;
	char	*plus_sign;

	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	equal_sign = ft_strchr(arg, '=');
	plus_sign = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus_sign && (!equal_sign || plus_sign < equal_sign))
	{
		export_with_append(arg, shell, plus_sign);
	}
	else if (equal_sign)
		export_with_value(arg, shell, equal_sign);
	else
	{
		if (!find_env_node(shell->env_list, arg))
			set_env_value(&shell->env_list, arg, NULL);
	}
	return (0);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	ret;

	if (!argv[1])
	{
		print_export_env(shell->env_list);
		return (0);
	}
	ret = 0;
	i = 1;
	while (argv[i])
	{
		if (export_var(argv[i], shell) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
