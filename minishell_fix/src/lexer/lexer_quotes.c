/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:41:15 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/30 17:41:15 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "builtin.h"
#include "minishell.h"
#include "error.h"

char	*handle_single_quote(const char *s, size_t *i)
{
	size_t	start;
	char	*result;

	start = *i;
	while (s[*i] != '\0' && s[*i] != '\'')
		(*i)++;
	if (s[*i] != '\'')
	{
		print_error(NULL, "unexpected EOF while looking for matching `''");
		return (NULL);
	}
	result = ft_strndup(s + start, *i - start);
	(*i)++;
	return (result);
}

static char	*expand_double_quote_part(const char *s, size_t *i, t_shell *shell)
{
	char	*part;

	if (s[*i] == '\\' && s[*i + 1] && (s[*i + 1] == '$'
			|| s[*i + 1] == '"' || s[*i + 1] == '\\'))
	{
		(*i)++;
		part = ft_strndup(s + *i, 1);
		(*i)++;
	}
	else if (s[*i] == '$')
		part = expand_variable(s, i, shell);
	else
	{
		part = ft_strndup(s + *i, 1);
		(*i)++;
	}
	return (part);
}

char	*handle_double_quote(const char *s, size_t *i, t_shell *shell)
{
	char	*result;
	char	*part;

	result = ft_strdup("");
	while (s[*i] != '\0' && s[*i] != '"')
	{
		part = expand_double_quote_part(s, i, shell);
		result = join_and_free(result, part);
	}
	if (s[*i] != '"')
	{
		print_error(NULL, "unexpected EOF while looking for matching `\"'");
		shell->exit_status = 2;
		free(result);
		return (NULL);
	}
	(*i)++;
	return (result);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
