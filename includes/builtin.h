/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		is_builtin(char *cmd);
int		execute_builtin(char **argv, t_env **env_list);

int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_env **env_list);
int		builtin_pwd(void);
int		builtin_export(char **argv, t_env **env_list);
int		builtin_unset(char **argv, t_env **env_list);
int		builtin_env(t_env *env_list);
int		builtin_exit(char **argv);

t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **env_list, t_env *new_node);
t_env	*find_env_node(t_env *env_list, char *key);
void	delete_env_node(t_env **env_list, char *key);
void	free_env_list(t_env *env_list);
char	**env_list_to_array(t_env *env_list);
t_env	*array_to_env_list(char **envp);

char	*get_env_value(t_env *env_list, char *key);
void	set_env_value(t_env **env_list, char *key, char *value);

#endif
