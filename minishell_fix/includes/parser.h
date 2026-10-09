/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 00:44:36 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 00:44:36 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "error.h"
# include <stdlib.h>

typedef struct s_shell	t_shell;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR,
	NODE_SEMICOLON
}	t_node_type;

typedef struct s_cmd_node
{
	char	**argv;
}	t_cmd_node;

typedef struct s_redir_node
{
	int				redir_type;
	char			*filename;
	struct s_node	*child;
	int				heredoc_fd;
}	t_redir_node;

typedef struct s_pipe_node
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe_node;

typedef struct s_semicolon_node
{
	struct s_node	*left;
	struct s_node	*right;
}	t_semicolon_node;

typedef struct s_node
{
	t_node_type	type;
	union
	{
		t_cmd_node			cmd;
		t_redir_node		redir;
		t_pipe_node			pipe;
		t_semicolon_node	semicolon;
	}	u_data;
}	t_node;

typedef struct s_parse_result
{
	t_node	*ast;
	int		error_code;
	char	*error_msg;
}	t_parse_result;

typedef struct s_lexer_result
{
	t_token	*tokens;
	int		error_code;
	char	*error_msg;
}	t_lexer_result;

t_node			*parse(t_token *tokens, t_shell *shell);
t_parse_result	*parse_with_error(t_token *tokens);
t_lexer_result	*lexer_with_error(const char *input);

#endif
