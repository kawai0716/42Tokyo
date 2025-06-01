/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 00:44:36 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 00:44:37 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <stdlib.h>

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR
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
}	t_redir_node;

typedef struct s_pipe_node
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe_node;

typedef struct s_node
{
	t_node_type	type;
	union
	{
		t_cmd_node		cmd;
		t_redir_node	redir;
		t_pipe_node		pipe;
	}	u_data;
}	t_node;

t_node	*parse(t_token *tokens);

#endif
