/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 04:16:31 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 04:16:31 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*init_env_list(char **envp)
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
