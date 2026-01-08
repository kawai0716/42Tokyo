/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:38:59 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/29 14:38:59 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"

typedef struct s_shell	t_shell;

typedef struct s_word_proc
{
	const char	*s;
	size_t		*i;
	char		**result;
	int			*has_content;
	t_shell		*shell;
}	t_word_proc;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	SEMICOLON
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token	*lexer(const char *input, t_shell *shell);
char	*expand_wildcard(const char *word);
char	*parse_word(const char *s, size_t *i, t_shell *shell);
char	*expand_variable(const char *s, size_t *i, t_shell *shell);
char	*handle_single_quote(const char *s, size_t *i);
char	*handle_double_quote(const char *s, size_t *i, t_shell *shell);
char	*join_and_free(char *s1, char *s2);
char	*expand_match_result(char *result, char *match);
int		handle_unquoted_var_expansion(t_token **tokens, const char *s,
			size_t *i, t_shell *shell);
int		process_word_part(t_word_proc *wp);
char	*parse_quoted_part(const char *s, size_t *i, t_shell *shell);
char	*parse_plain_part(const char *s, size_t *i, t_shell *shell);

#endif
