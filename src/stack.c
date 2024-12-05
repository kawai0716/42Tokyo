/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:37 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 19:26:22 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

t_stack	*stack_bottom(t_stack *stack)
{
	while (stack != NULL && stack->next != NULL)
		stack = stack->next;
	return (stack);
}

t_stack	*stack_second_bottom(t_stack *stack)
{
	while (stack != NULL && stack->next != NULL && stack->next->next != NULL)
		stack = stack->next;
	return (stack);
}
