/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:41:15 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/30 17:41:17 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_whitespace(char c);
int		is_metachar(char c);

static char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

static char	*parse_quoted_part(const char *s, size_t *i)
{
	char	*part;
	char	quote;
	size_t	start;

	quote = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] != '\0' && s[*i] != quote)
		(*i)++;
	part = ft_strndup(s + start, *i - start);
	if (s[*i] == quote)
		(*i)++;
	return (part);
}

static char	*parse_plain_part(const char *s, size_t *i)
{
	char	*part;

	part = ft_strndup(s + *i, 1);
	(*i)++;
	return (part);
}

char	*parse_word(const char *s, size_t *i)
{
	char	*result;
	char	*part;

	result = NULL;
	while (s[*i] != '\0'
		&& !is_whitespace(s[*i])
		&& !is_metachar(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			part = parse_quoted_part(s, i);
		else
			part = parse_plain_part(s, i);
		result = join_and_free(result, part);
	}
	return (result);
}
