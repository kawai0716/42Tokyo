/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 01:12:24 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/02 01:12:24 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "parser.h"
# include "builtin.h"
# include "minishell.h"
# include <readline/readline.h> 
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_shell	t_shell;

typedef struct s_heredoc
{
	const char	*finish_str;
	int			*fd;
	t_shell		*shell;
}	t_heredoc;

typedef struct s_pipe_data
{
	int		fd[2];
	int		fd_in;
	t_node	*cmd;
	t_shell	*shell;
}	t_pipe_data;

typedef struct s_redir_exec
{
	t_node	**redirs;
	int		redir_count;
	t_node	*base_cmd;
	t_shell	*shell;
}	t_redir_exec;

void	ex_main(t_node *g_cmd, t_shell *shell);
void	run_simple_cmd(t_node *cmd, t_shell *shell);
void	execute_node(t_node *cmd, t_shell *shell);
int		redirect_check(t_node *cmd, t_shell *shell);
void	exec_cmd(t_node *cmd, t_shell *shell);
int		is_builtin(char *cmd);
int		execute_builtin(char **argv, t_shell *shell);
int		read_heredoc_to_pipe(const char *finish_str, t_shell *shell);
int		process_heredoc_line(char *line, t_heredoc *h, int *done);
int		process_heredoc_loop(int fd[2], const char *finish_str, t_shell *shell);
char	*find_cmd_path(const char *cmd, t_shell *shell);
void	pipeline_child(t_pipe_data *pd);
pid_t	create_first_child(t_pipe_data *pd, t_node *left);
pid_t	create_second_child(t_pipe_data *pd, t_node *right);
void	handle_env_error(t_shell *shell);
void	handle_cmd_not_found_exec(char **envp, char *cmd_name, t_shell *shell);

void	execute_redir_external(t_node *cmd, t_redir_exec *re);
void	handle_builtin_redirection(t_node *cmd, t_node **redirs,
			int redir_count, t_shell *shell);
t_node	*collect_redirections(t_node *cmd, t_node **redirs, int *count);
int		execute_redirections(t_node **redirs, int count, t_shell *shell);

int		is_assignment(const char *str);
int		process_assignment(const char *str, t_shell *shell);
int		process_assignments(char **argv, char ***new_argv, t_shell *shell);

int		ft_strcmp(const char *s1, const char *s2);
void	free_split(char **split);

#endif
