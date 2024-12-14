/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:41 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/15 06:40:55 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

static void	swap(t_stack *stack)
{
	int	n;

	if (!stack && !stack->next)
		return ;
	n = stack->value;
	stack->value = stack->next->value;
	stack->next->value = n;
	n = stack->index;
	stack->index = stack->next->index;
	stack->next->index = n;
}

void	sa(t_stack **stack)
{
	swap(*stack);
	ft_putstr("sa\n");
}

void	sb(t_stack **stack)
{
	swap(*stack);
	ft_putstr("sb\n");
}

void	ss(t_stack **stack_a, t_stack **stack_b)
{
	swap(*stack_a);
	swap(*stack_b);
	ft_putstr("ss\n");
}
