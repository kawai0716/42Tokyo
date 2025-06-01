/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:56:03 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/29 14:56:05 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_whitespace(char c);
int		is_metachar(char c);
t_token	*add_token(t_token **head, char *value, t_token_type type);
char	*parse_word(const char *s, size_t *i);

static void	skip_whitespace(const char *s, size_t *i)
{
	while (s[*i] != '\0' && is_whitespace(s[*i]))
		(*i)++;
}

static void	handle_operator(t_token **tokens, const char *s, size_t *i)
{
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		add_token(tokens, ft_strndup(">>", 2), REDIR_APPEND);
		*i += 2;
	}
	else if (s[*i] == '<' && s[*i + 1] == '<')
	{
		add_token(tokens, ft_strndup("<<", 2), HEREDOC);
		*i += 2;
	}
	else if (s[*i] == '>')
	{
		add_token(tokens, ft_strndup(">", 1), REDIR_OUT);
		(*i)++;
	}
	else if (s[*i] == '<')
	{
		add_token(tokens, ft_strndup("<", 1), REDIR_IN);
		(*i)++;
	}
	else if (s[*i] == '|')
	{
		add_token(tokens, ft_strndup("|", 1), PIPE);
		(*i)++;
	}
}

static void	handle_word(t_token **tokens, const char *s, size_t *i)
{
	char	*word;

	word = parse_word(s, i);
	add_token(tokens, word, WORD);
}

t_token	*lexer(const char *s)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (is_whitespace(s[i]))
			skip_whitespace(s, &i);
		else if (is_metachar(s[i]))
			handle_operator(&tokens, s, &i);
		else
			handle_word(&tokens, s, &i);
	}
	return (tokens);
}
