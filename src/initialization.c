/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:50:55 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/11 17:48:25 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

t_stack	*stack_new(int value)
{
	t_stack	*new;

	new = malloc(sizeof * new);
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
