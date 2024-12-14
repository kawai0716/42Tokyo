/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:15:00 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/15 06:39:57 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

static void	move_stack_b(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_size;
	int	push_count;
	int	i;

	stack_size = count_stack(*stack_a);
	push_count = 0;
	i = 0;
	while (stack_size > 6 && stack_size / 2 > push_count && stack_size < i)
	{
		if ((*stack_a)->index <= stack_size / 2)
		{
			pb(stack_a, stack_b);
			push_count++;
		}
		else
		{
			ra(stack_a);
			i++;
		}
	}
	while (stack_size - push_count > 3)
	{
		pb(stack_a, stack_b);
		push_count++;
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

static void	last_check_stack(t_stack **a)
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

void	sort(t_stack **stack_a, t_stack **stack_b)
{
	move_stack_b(stack_a, stack_b);
	three_sort(stack_a);
	get_pos(stack_a);
	get_pos(stack_b);
	while (*stack_b)
	{
		get_target_pos(stack_a, stack_b);
		cost(stack_a, stack_b);
		fastest_move(stack_a, stack_b);
	}
	if (!sorted(*stack_a))
		last_check_stack(stack_a);
}
