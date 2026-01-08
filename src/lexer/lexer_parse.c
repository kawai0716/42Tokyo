/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
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

int		is_whitespace(char c);
int		is_metachar(char c);
char	*expand_variable(const char *s, size_t *i, t_shell *shell);
char	*handle_single_quote(const char *s, size_t *i);
char	*handle_double_quote(const char *s, size_t *i, t_shell *shell);
char	*join_and_free(char *s1, char *s2);

char	*parse_quoted_part(const char *s, size_t *i, t_shell *shell)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	if (quote == '\'')
		return (handle_single_quote(s, i));
	else if (quote == '"')
		return (handle_double_quote(s, i, shell));
	else if (quote == '`')
	{
		shell->exit_status = 2;
		return (NULL);
	}
	return (NULL);
}

static char	*handle_wildcard_expansion(char *result)
{
	char	*expanded;

	if (result)
	{
		expanded = expand_wildcard(result);
		free(result);
		return (expanded);
	}
	return (result);
}

char	*parse_plain_part(const char *s, size_t *i, t_shell *shell)
{
	char	*part;

	if (s[*i] == '\\' && s[*i + 1] != '\0')
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

char	*parse_word(const char *s, size_t *i, t_shell *shell)
{
	char		*result;
	int			has_content;
	t_word_proc	wp;

	result = NULL;
	has_content = 0;
	while (s[*i] != '\0' && !is_whitespace(s[*i]) && !is_metachar(s[*i]))
	{
		wp.s = s;
		wp.i = i;
		wp.result = &result;
		wp.has_content = &has_content;
		wp.shell = shell;
		if (!process_word_part(&wp))
			return (NULL);
	}
	if (!has_content && result && result[0] == '\0')
	{
		free(result);
		return (NULL);
	}
	return (handle_wildcard_expansion(result));
}
