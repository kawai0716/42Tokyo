/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:45:01 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 10:45:01 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*create_redir_node(
	t_token_type redir_type, char *filename, t_node *child)
{
	t_node	*redir;

	redir = malloc(sizeof(t_node));
	if (!redir)
		return (NULL);
	redir->type = NODE_REDIR;
	redir->u_data.redir.redir_type = redir_type;
	redir->u_data.redir.filename = filename;
	redir->u_data.redir.child = child;
	redir->u_data.redir.heredoc_fd = -1;
	return (redir);
}

static char	*dup_filename(t_token **tokens)
{
	char	*filename;

	if (!*tokens || (*tokens)->type != WORD)
		return (NULL);
	filename = ft_strdup((*tokens)->value);
	*tokens = (*tokens)->next;
	return (filename);
}

t_node	*parse_redirection(t_token **tokens, t_node *child)
{
	t_token_type	redir_type;
	char			*filename;

	if (!*tokens)
		return (NULL);
	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	filename = dup_filename(tokens);
	if (!filename)
		return (NULL);
	return (create_redir_node(redir_type, filename, child));
}
