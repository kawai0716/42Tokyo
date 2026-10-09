/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 09:08:56 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 09:08:56 by yuhashim         ###   ########.fr       */
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

static void	free_envp_partial(char **envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static char	*create_env_string(t_env *node)
{
	size_t	len;
	char	*env_str;

	if (!node->value)
		return (ft_strdup(node->key));
	len = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	env_str = malloc(len);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, node->key, len);
	ft_strlcat(env_str, "=", len);
	ft_strlcat(env_str, node->value, len);
	return (env_str);
}

char	**env_list_to_array(t_env *env_list)
{
	char	**envp;
	t_env	*current;
	size_t	i;

	envp = malloc(sizeof(char *) * (env_list_size(env_list) + 1));
	if (!envp)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		envp[i] = create_env_string(current);
		if (!envp[i])
		{
			free_envp_partial(envp, i);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	process_env_entry(t_env **env_list, char *envp_entry)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*new_node;

	equal_sign = ft_strchr(envp_entry, '=');
	if (!equal_sign)
		return ;
	key = ft_substr(envp_entry, 0, equal_sign - envp_entry);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
	{
		if (key)
			free(key);
		if (value)
			free(value);
		return ;
	}
	new_node = create_env_node(key, value);
	free(key);
	free(value);
	if (new_node)
		add_env_node(env_list, new_node);
}
