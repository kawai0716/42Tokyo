/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:05:17 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 21:39:17 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	cost(t_stack **a, t_stack **b)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;
	int		cs_a;
	int		cs_b;

	tmp_a = *a;
	tmp_b = *b;
	cs_a = count_stack(tmp_a);
	cs_b = count_stack(tmp_b);
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
