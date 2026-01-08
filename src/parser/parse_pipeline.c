/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:44:46 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 10:44:46 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_command(t_token **tokens);

static t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_node	*pipe;

	pipe = malloc(sizeof(t_node));
	if (!pipe)
		return (NULL);
	pipe->type = NODE_PIPE;
	pipe->u_data.pipe.left = left;
	pipe->u_data.pipe.right = right;
	return (pipe);
}

t_node	*parse_pipeline(t_token **tokens)
{
	t_node	*left;
	t_node	*right;

	left = parse_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_command(tokens);
		if (!right)
			return (NULL);
		left = create_pipe_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}
