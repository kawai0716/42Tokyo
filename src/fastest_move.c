/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fastest_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:32:36 by marvin            #+#    #+#             */
/*   Updated: 2024/12/09 19:32:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void fastest_move(t_stack **a, t_stack **b)
{
    t_stack *tmp_b;
    int smallest;

    tmp_b = *b;
    smallest = INT_MAX;
    while(tmp_b)
    {
        if(change_plus(tmp_b->cost_a) + change_plus(tmp_b->cost_b) < change_plus(smallest))
        {
            smallest = change_plus(tmp_b->cost_a) + change_plus(tmp_b->cost_b);
            
        }
        tmp_b = tmp_b->next;
    }
    
}
