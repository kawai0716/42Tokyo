/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:35:37 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/05 17:35:37 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_pipeline(t_token **tokens);

static t_node	*create_semicolon_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)safe_malloc(sizeof(t_node), "create_semicolon_node");
	if (!node)
		return (NULL);
	node->type = NODE_SEMICOLON;
	node->u_data.semicolon.left = left;
	node->u_data.semicolon.right = right;
	return (node);
}

t_node	*parse_semicolon(t_token **tokens)
{
	t_node	*left;
	t_node	*right;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == SEMICOLON)
	{
		*tokens = (*tokens)->next;
		if (!*tokens)
			return (left);
		right = parse_semicolon(tokens);
		if (!right)
			return (left);
		left = create_semicolon_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}
