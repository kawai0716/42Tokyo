/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:44:30 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 10:44:30 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse_redirection(t_token **tokens, t_node *child);

int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

static int	count_word_token(t_token **current, size_t *count)
{
	if ((*current)->type == WORD && (*current)->value)
	{
		(*count)++;
		*current = (*current)->next;
	}
	else if (is_redirection((*current)->type))
	{
		*current = (*current)->next;
		if (*current && (*current)->type == WORD)
			*current = (*current)->next;
	}
	else
		return (0);
	return (1);
}

size_t	count_words(t_token *tokens)
{
	size_t	count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && count_word_token(&current, &count))
		;
	return (count);
}

void	free_argv_partial(char **argv, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	process_token(t_token **tokens, char **argv, size_t *i)
{
	if ((*tokens)->type == WORD && (*tokens)->value)
	{
		argv[*i] = ft_strdup((*tokens)->value);
		if (!argv[*i])
			return (0);
		(*i)++;
		*tokens = (*tokens)->next;
	}
	else if (is_redirection((*tokens)->type))
	{
		*tokens = (*tokens)->next;
		if (*tokens && (*tokens)->type == WORD)
			*tokens = (*tokens)->next;
	}
	else
		return (-1);
	return (1);
}
