/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:03:30 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/15 09:12:18 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	cost(t_stack **a, t_stack **b)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		cs_a;
	int		cs_b;

	tmp_a = *a;
	tmp_b = *b;
	cs_a = count_stack(*a);
	cs_b = count_stack(*b);
	while (tmp_b)
	{
		if (tmp_b->pos <= cs_b / 2)
			tmp_b->cost_b = tmp_b->pos;
		else
			tmp_b->cost_b = (cs_b - tmp_b->pos) * -1;
		if (tmp_b->target_pos <= cs_a / 2)
			tmp_b->cost_a = tmp_b->target_pos;
		else
			tmp_b->cost_a = (cs_a - tmp_b->target_pos) * -1;
		tmp_b = tmp_b->next;
	}
}
