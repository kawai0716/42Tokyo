/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:31:23 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 19:21:50 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	get_pos(t_stack **stack)
{
	t_stack	*s;
	int		i;

	s = *stack;
	i = 0;
	while (s)
	{
		s->pos = i;
		s = s->next;
		i++;
	}
}

static int	get_target(t_stack **a, int index_b, int target_pos, int max)
{
	t_stack	*tmp_a;

	tmp_a = *a;
	while (tmp_a)
	{
		if (tmp_a->index > index_b && tmp_a->index < max)
		{
			max = tmp_a->index;
			target_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	if (max != INT_MAX)
		return (target_pos);
	tmp_a = *a;
	while (tmp_a)
	{
		if (tmp_a->index < max)
		{
			max = tmp_a->index;
			target_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	return (target_pos);
}

void	get_target_pos(t_stack **a, t_stack **b)
{
	int		target_pos;
	t_stack	*tmp_b;

	target_pos = 0;
	tmp_b = *b;
	while (tmp_b)
	{
		target_pos = get_target(a, tmp_b->index, target_pos, INT_MAX);
		tmp_b->target_pos = target_pos;
		tmp_b = tmp_b->next;
	}
}
