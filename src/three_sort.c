/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:47 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/15 08:17:00 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	three_sort(t_stack **stack)
{
	int	highest_index_number;

	if (sorted(*stack))
		return ;
	highest_index_number = 3;
	if ((*stack)->index == highest_index_number)
		ra(stack);
	else if ((*stack)->next->index == highest_index_number)
		rra(stack);
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}
