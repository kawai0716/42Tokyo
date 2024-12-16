/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:06:55 by marvin            #+#    #+#             */
/*   Updated: 2024/12/16 18:06:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	move_stack_b(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_size;
	int	pushed;
	int	i;

	stack_size = get_stack_size(*stack_a);
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
	t_stack	*tmp_a;
	int		lowest_index;
	int		lowest_pos;

	get_pos(a);
	tmp_a = *a;
	lowest_index = INT_MAX;
	while (tmp_a)
	{
		if (tmp_a->index < lowest_index)
		{
			lowest_index = tmp_a->index;
			lowest_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	return (lowest_pos);
}

static void	last_check_stack(t_stack **stack_a)
{
	int	size;
	int	lowest_num_pos;

	size = count_stack(*a);
	lowest_num_pos = lowest_number_pos(a);
	if (lowest_num_pos <= size / 2)
	{
		while (lowest_num_pos > 0)
		{
			ra(a);
			lowest_num_pos--;
		}
	}
	else
	{
		while (lowest_num_pos < size)
		{
			rra(a);
			lowest_num_pos++;
		}
	}
}

sort(t_stack **stack_a, t_stack **stack_b)
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
