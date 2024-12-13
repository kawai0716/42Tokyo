/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:35:08 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/11 17:39:46 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

static void	both_r(t_stack **a, t_stack **b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		rr(a, b);
		*cost_a--;
		*cost_b--;
	}
}

static void	both_rr(t_stack **a, t_stack **b, int *cost_a, int *cost_b)
{
	while (*cost_a < 0 || *cost_b < 0)
	{
		rrr(a, b);
		*cost_a++;
		*cost_b++;
	}
}

static void	a_r_rr(t_stack **a, int *cost_a)
{
	if (*cost_a > 0)
	{
		ra(a);
		*cost_a--;
	}
	else if (*cost_a < 0)
	{
		rra(a);
		*cost_a++;
	}
}

static void	b_r_rr(t_stack **b, int *cost_b)
{
	if (*cost_b > 0)
	{
		rb(b);
		*cost_b--;
	}
	else if (*cost_b < 0)
	{
		rrb(b);
		*cost_b++;
	}
}

void	optimal_move(t_stack **a, t_stack **b, int cost_a, int cost_b)
{
	if (cost_a > 0 && cost_b > 0)
		both_r(a, b, &cost_a, &cost_b);
	else if (cost_a < 0 && cost_b < 0)
		both_rr(a, b, &cost_a, &cost_b);
	if (cost_a != 0 && cost_b == 0)
		a_r_rr(a, &cost_a);
	else if (cost_a == 0 && cost_b != 0)
		b_r_rr(b, &cost_b);
	pa(a, b);
}
