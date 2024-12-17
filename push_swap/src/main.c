/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:05:57 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 16:38:56 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sorted(t_stack *stack)
{
	while (stack->next != NULL)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

static void	push_swap(t_stack **stack_a, t_stack **stack_b, int stack_size)
{
	if (stack_size == 2 && !sorted(*stack_a))
		sa(stack_a);
	else if (stack_size == 3 && !sorted(*stack_a))
		three_sort(stack_a);
	else if (stack_size > 3 && !sorted(*stack_a))
		sort(stack_a, stack_b);
}

int	main(int ac, char **av)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		i;

	if (ac < 2)
		return (0);
	if (!check_number(av))
		exit_error(NULL, NULL);
	stack_b = NULL;
	stack_a = fill_stack(ac, av);
	i = count_stack(stack_a);
	index_number(stack_a, i + 1);
	push_swap(&stack_a, &stack_b, i);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
