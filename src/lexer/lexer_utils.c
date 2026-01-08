/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:19:39 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/30 16:19:39 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

t_token	*add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*cur;

	new = (t_token *)safe_malloc(sizeof(t_token), "add_token");
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
	}
	return (new);
}
