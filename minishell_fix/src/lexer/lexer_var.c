/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:41:15 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/30 17:41:15 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_whitespace(char c);
int	is_metachar(char c);

int	is_standalone_var(const char *s, size_t start)
{
	size_t	i;

	i = start;
	if (s[i] != '$' || !s[i + 1])
		return (0);
	i++;
	if (s[i] == '?')
		i++;
	else if (ft_isdigit(s[i]))
		i++;
	else
	{
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	}
	return (!s[i] || is_whitespace(s[i]) || is_metachar(s[i]));
}
