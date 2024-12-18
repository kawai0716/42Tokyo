/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:06:55 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 19:45:00 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_stack_b(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_size;
	int	pushed;
	int	i;

	stack_size = count_stack(*stack_a);
	pushed = 0;
	i = 0;
	while (stack_size > 6 && i < stack_size && pushed < stack_size / 2)
	{
		if ((*stack_a)->index <= stack_size / 2)
		{
			pb(stack_a, stack_b);
			pushed++;
		}
		else
			ra(stack_a);
		i++;
	}
	while (stack_size - pushed > 3)
	{
		pb(stack_a, stack_b);
		pushed++;
	}
}

static int	lowest_number_pos(t_stack **a)
{
	t_stack	*tmp;
	int		lowest_index;
	int		lowest_pos;

	tmp = *a;
	lowest_index = INT_MAX;
	get_position(a);
	lowest_pos = tmp->pos;
	while (tmp)
	{
		if (tmp->index < lowest_index)
		{
			lowest_index = tmp->index;
			lowest_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (lowest_pos);
}

static void	last_check_stack(t_stack **stack_a)
{
	int	lowest_pos;
	int	stack_size;

	stack_size = count_stack(*stack_a);
	lowest_pos = lowest_number_pos(stack_a);
	if (lowest_pos > stack_size / 2)
	{
		while (lowest_pos < stack_size)
		{
			rra(stack_a);
			lowest_pos++;
		}
	}
	else
	{
		while (lowest_pos > 0)
		{
			ra(stack_a);
			lowest_pos--;
		}
	}
}

void	sort(t_stack **stack_a, t_stack **stack_b)
{
	move_stack_b(stack_a, stack_b);
	three_sort(stack_a);
	while (*stack_b)
	{
		get_target_position(stack_a, stack_b);
		cost(stack_a, stack_b);
		fastest_move(stack_a, stack_b);
	}
	if (!sorted(*stack_a))
		last_check_stack(stack_a);
}
