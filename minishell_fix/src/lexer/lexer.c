/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:56:03 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/29 14:56:03 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int		is_whitespace(char c);
int		is_metachar(char c);
t_token	*add_token(t_token **head, char *value, t_token_type type);
char	*parse_word(const char *s, size_t *i, t_shell *shell);
int		handle_unquoted_var_expansion(t_token **tokens, const char *s,
			size_t *i, t_shell *shell);
int		is_standalone_var(const char *s, size_t start);

static void	skip_whitespace(const char *s, size_t *i)
{
	while (s[*i] != '\0' && is_whitespace(s[*i]))
		(*i)++;
}

static void	handle_redir_ops(t_token **tokens, const char *s, size_t *i)
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
}

static void	handle_operator(t_token **tokens, const char *s, size_t *i)
{
	if (s[*i] == '>' || s[*i] == '<')
		handle_redir_ops(tokens, s, i);
	else if (s[*i] == '|')
	{
		add_token(tokens, ft_strndup("|", 1), PIPE);
		(*i)++;
	}
	else if (s[*i] == ';')
	{
		add_token(tokens, ft_strndup(";", 1), SEMICOLON);
		(*i)++;
	}
}

static int	handle_word(t_token **tokens, const char *s, size_t *i,
	t_shell *shell)
{
	char	*word;
	size_t	start;

	start = *i;
	if (is_standalone_var(s, start))
	{
		if (handle_unquoted_var_expansion(tokens, s, i, shell))
			return (1);
		*i = start;
	}
	word = parse_word(s, i, shell);
	if (word)
		add_token(tokens, word, WORD);
	return (1);
}

t_token	*lexer(const char *s, t_shell *shell)
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
		{
			if (!handle_word(&tokens, s, &i, shell))
			{
				return (NULL);
			}
		}
	}
	return (tokens);
}
