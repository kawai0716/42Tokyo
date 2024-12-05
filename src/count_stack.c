/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:50:37 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 19:26:01 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

int	count_stack(t_stack *stack)
{
	int	count;

	count = 0;
	if (!stack)
		return (0);
	while (stack != NULL)
	{
		stack = stack->next;
		count++;
	}
	return (count);
}
