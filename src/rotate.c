/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:20 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 19:26:17 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

static void	rotate(t_stack **stack)
{
	t_stack	*s;
	t_stack	*s2;

	s = *stack;
	*stack = s->next;
	s2 = move_stack_bottom(*stack);
	s->next = NULL;
	s2->next = s;
}

void	ra(t_stack **stack_a)
{
	rotate(stack_a);
	ft_putstr("ra");
}

void	rb(t_stack **stack_b)
{
	rotate(stack_b);
	ft_putstr("rb");
}

void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	ft_putstr("rr");
}
