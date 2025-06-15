/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:12:24 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 01:12:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include <readline/readline.h> 
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

char **g_envp = NULL;
t_node *g_cmd  = NULL;

void ex_main(t_node *g_cmd);
void run_simple_cmd(t_node *cmd);
void execute_node(t_node *cmd);
void redirect_check(t_node *cmd);
void ex_main(t_node *g_cmd);
void exec_cmd(t_node *cmd);
void redirect_check(t_node *cmd);

//utils.c
int	ft_strcmp(const char *s1, const char *s2);

#endif