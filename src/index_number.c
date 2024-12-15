/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:50:47 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/15 08:08:53 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	index_number(t_stack *stack, int stack_size)
{
	t_stack	*s;
	t_stack	*top_number;
	int		i;

	while (--stack_size > 0)
	{
		s = stack;
		top_number = NULL;
		i = INT_MIN;
		while (s)
		{
			if (s->value == INT_MIN && s->index == 0)
				s->index = 1;
			if (s->value > i && s->index == 0)
			{
				i = s->value;
				top_number = s;
				s = stack;
			}
			else
				s = s->next;
		}
		if (top_number != NULL)
			top_number->index = stack_size;
	}
}
