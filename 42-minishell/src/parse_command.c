/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:44:30 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 10:44:31 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_redirection(t_token **tokens, t_node *child);

static int	is_redirection(t_token_type type)
{
	return (
		type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC
	);
}

static char	**dup_argv(t_token **tokens)
{
	size_t	count;
	size_t	i;
	char	**argv;

	count = 0;
	while (tokens[count] && tokens[count]->type == WORD)
		count++;
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && (*tokens)->type == WORD)
	{
		argv[i++] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_node	*parse_command(t_token **tokens)
{
	t_node	*cmd;

	cmd = malloc(sizeof(t_node));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_CMD;
	cmd->u_data.cmd.argv = dup_argv(tokens);
	if (!cmd->u_data.cmd.argv)
		return (NULL);
	while (*tokens && is_redirection((*tokens)->type))
	{
		cmd = parse_redirection(tokens, cmd);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}
