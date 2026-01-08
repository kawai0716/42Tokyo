/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var_split.c                                  :+:      :+:    :+:   */
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
t_token	*add_token(t_token **head, char *value, t_token_type type);

static void	free_remaining_words(char **words, int start)
{
	while (words[start])
		free(words[start++]);
	free(words);
}

static int	add_words_to_tokens(t_token **tokens, char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		if (words[i][0] != '\0')
		{
			if (!add_token(tokens, ft_strdup(words[i]), WORD))
			{
				free_remaining_words(words, i);
				return (0);
			}
		}
		free(words[i]);
		i++;
	}
	free(words);
	return (1);
}

static int	add_split_words(t_token **tokens, char *value)
{
	char	**words;

	if (!value || !*value)
	{
		free(value);
		return (1);
	}
	words = ft_split(value, ' ');
	free(value);
	if (!words)
		return (0);
	return (add_words_to_tokens(tokens, words));
}

int	handle_unquoted_var_expansion(t_token **tokens, const char *s,
	size_t *i, t_shell *shell)
{
	char	*value;

	if (s[*i] != '$')
		return (0);
	value = expand_variable(s, i, shell);
	if (!value)
		return (0);
	if (ft_strchr(value, ' ') || ft_strchr(value, '\t'))
		return (add_split_words(tokens, value));
	if (*value)
		return (add_token(tokens, value, WORD) != NULL);
	free(value);
	return (1);
}
