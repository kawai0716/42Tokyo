/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*node;

	node = find_env_node(env_list, key);
	if (node)
		return (node->value);
	return (NULL);
}

void	set_env_value(t_env **env_list, char *key, char *value)
{
	t_env	*node;
	t_env	*new_node;

	node = find_env_node(*env_list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		new_node = create_env_node(key, value);
		if (new_node)
			add_env_node(env_list, new_node);
	}
}
