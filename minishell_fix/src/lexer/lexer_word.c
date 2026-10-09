/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:44:13 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/21 16:44:13 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"
#include "error.h"

int	process_word_part(t_word_proc *wp)
{
	char	*part;

	if (wp->s[*(wp->i)] == '\'' || wp->s[*(wp->i)] == '"'
		|| wp->s[*(wp->i)] == '`')
	{
		part = parse_quoted_part(wp->s, wp->i, wp->shell);
		if (!part)
			return (0);
		*(wp->has_content) = 1;
	}
	else
	{
		part = parse_plain_part(wp->s, wp->i, wp->shell);
		if (!part)
			return (0);
		if (*part)
			*(wp->has_content) = 1;
	}
	*(wp->result) = join_and_free(*(wp->result), part);
	return (*(wp->result) != NULL);
}
