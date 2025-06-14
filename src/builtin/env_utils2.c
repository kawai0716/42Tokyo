/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static size_t	env_list_size(t_env *env_list)
{
	size_t	count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env_list)
{
	char	**envp;
	t_env	*current;
	size_t	i;
	size_t	len;
	char	*env_str;

	envp = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	if (!envp)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		len = ft_strlen(current->key) + ft_strlen(current->value) + 2;
		env_str = malloc(len);
		if (!env_str)
			return (NULL);
		ft_strlcpy(env_str, current->key, len);
		ft_strlcat(env_str, "=", len);
		ft_strlcat(env_str, current->value, len);
		envp[i++] = env_str;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

static void	process_env_entry(t_env **env_list, char *envp_entry)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*new_node;

	equal_sign = ft_strchr(envp_entry, '=');
	if (equal_sign)
	{
		key = ft_substr(envp_entry, 0, equal_sign - envp_entry);
		value = ft_strdup(equal_sign + 1);
		new_node = create_env_node(key, value);
		if (new_node)
			add_env_node(env_list, new_node);
		free(key);
		free(value);
	}
}

t_env	*array_to_env_list(char **envp)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		process_env_entry(&env_list, envp[i]);
		i++;
	}
	return (env_list);
}
