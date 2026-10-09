/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:13 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/27 18:02:13 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "builtin.h"
# include "lexer.h"
# include "parser.h"

# define MODE_INTERACTIVE 0
# define MODE_HEREDOC     1
# define MODE_EXECUTING   2

typedef struct s_gnl_data
{
	char	*buffer;
	char	*leftover;
	int		buffer_size;
}	t_gnl_data;

typedef struct s_input_buffer
{
	char	**lines;
	int		current;
	int		total;
}	t_input_buffer;

typedef struct s_shell
{
	int				shell_mode;
	char			**envp;
	t_env			*env_list;
	int				exit_status;
	int				should_exit;
	t_gnl_data		*gnl_data;
	t_gnl_data		*heredoc_gnl_data;
	t_input_buffer	*input_buffer;
	int				heredoc_buffer_index;
	t_node			*current_ast;
	t_token			*current_tokens;
	char			*current_line;
	char			*current_cmd;
}	t_shell;

extern volatile sig_atomic_t	g_signal_received;

void	init_signal(void);
void	set_execution_signal(void);
void	restore_interactive_signal(void);
void	set_child_signal_default(void);
void	signal_handler_interactive(int signum);
void	signal_handler_executing(int signum);
t_shell	*init_shell(char **envp);
void	free_tokens(t_token *tokens);
void	free_ast(t_node *ast);
char	**dup_envp(char **envp);
void	execute_node(t_node *cmd, t_shell *shell);
void	free_envp_array(char **envp);
void	cleanup_shell(t_shell *shell);
void	minishell_loop(char **envp);
void	process_line(char *line, t_shell *shell);
void	handle_signal(t_shell *shell);
void	cleanup_shell_for_exec(t_shell *shell);
char	*get_next_line_minishell(t_gnl_data *data);

#endif
