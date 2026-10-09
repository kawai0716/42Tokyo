/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer6.c                                           :+:      :+:    :+:   */
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

static char	*handle_special_vars(const char *s, size_t *i, t_shell *shell)
{
	char	*result;

	if (s[*i] == '?')
	{
		(*i)++;
		result = ft_itoa(shell->exit_status);
		return (result);
	}
	if (ft_isdigit(s[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}

char	*expand_variable(const char *s, size_t *i, t_shell *shell)
{
	size_t	start;
	char	*var_name;
	char	*value;
	char	*result;

	(*i)++;
	result = handle_special_vars(s, i, shell);
	if (result)
		return (result);
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	if (*i == start)
		return (ft_strdup("$"));
	var_name = ft_strndup(s + start, *i - start);
	value = get_env_value(shell->env_list, var_name);
	free(var_name);
	if (value)
		result = ft_strdup(value);
	else
		result = ft_strdup("");
	return (result);
}
