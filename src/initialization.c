/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:50:55 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 21:09:55 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	free_stack(t_stack **stack)
{
	t_stack	*t;

	if (!stack || !(*stack))
		return ;
	while (*stack)
	{
		t = (*stack)->next;
		free(*stack);
		*stack = t;
	}
	*stack = NULL;
}

void	exit_error(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_a != NULL, *stack_a != NULL)
		free_stack(stack_a);
	if (stack_b != NULL, *stack_b != NULL)
		free_stack(stack_a);
	write(2, "ERROR\n", 6);
	exit(1);
}

t_stack	*stack_new(int value)
{
	t_stack	*new;

	new = malloc(sizeof *new);
	if (!new)
		return (NULL);
	new->value = value;
	new->index = 0;
	new->pos = -1;
	new->target_pos = -1;
	new->cost_a = -1;
	new->cost_b = -1;
	new->next = NULL;
}

t_stack	*move_stack_bottom(t_stack *stack)
{
	while (stack && stack->next != NULL)
		stack = stack->next;
	return (stack);
}

void	stack_add_botom(t_stack **stack, t_stack *new)
{
	t_stack	*move;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	move = move_stack_bottom(*stack);
	move->next = new;
}

t_stack	*fill_stack(int ac, char **av)
{
	long int	n;
	int			i;
	t_stack		*stack_a;

	n = 0;
	i = 1;
	while (i < ac)
	{
		n = ft_atoi(av[i]);
		if (INT_MAX < n || n < INT_MIN)
			exit_error(&stack_a, NULL);
		if (i == 1)
			stack_a = stack_new((int)n);
		else
			stack_add_botom(&stack_a, stack_new((int)n));
		i++;
	}
	return (stack_a);
}
