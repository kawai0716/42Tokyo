/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fastest_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:32:36 by marvin            #+#    #+#             */
/*   Updated: 2024/12/15 06:27:37 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	fastest_move(t_stack **a, t_stack **b)
{
	t_stack	*tmp_b;
	int		smallest;
	int		c_a;
	int		c_b;

	tmp_b = *b;
	smallest = INT_MAX;
	while (tmp_b)
	{
		if (change_plus(tmp_b->cost_a)
			+ change_plus(tmp_b->cost_b) < change_plus(smallest))
		{
			smallest = change_plus(tmp_b->cost_a) + change_plus(tmp_b->cost_b);
			c_a = tmp_b->cost_a;
			c_b = tmp_b->cost_b;
		}
		tmp_b = tmp_b->next;
	}
	optimal_move(a, b, c_a, c_b);
}
