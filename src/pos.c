/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:31:23 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 23:02:29 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

void	get_pos(t_stack **stack)
{
	t_stack	*s;
	int		i;

	s = *stack;
	i = 0;
	while (s)
	{
		s->pos = i;
		s = s->next;
		i++;
	}
}

static int	get_target(t_stack **a, int index_b, int target_pos,
		int target_index)
{
	t_stack	*tmp_a;

	tmp_a = *a;
	while (tmp_a)
	{
		if (tmp_a->index > index_b && tmp_a->index < target_index)
		{
			target_index = tmp_a->index;
			target_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	if (target_index != INT_MAX)
		return (target_pos);
	tmp_a = *a;
	while (tmp_a)
	{
		if (tmp_a->index < target_index)
		{
			target_index = tmp_a->index;
			target_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	return (target_pos);
}

void	get_target_pos(t_stack **a, t_stack **b)
{
	int		target_pos;
	t_stack	*tmp_b;

	target_pos = 0;
	tmp_b = *b;
	while (tmp_b)
	{
		target_pos = get_target(a, tmp_b->index, target_pos, INT_MAX);
		tmp_b->target_pos = target_pos;
		tmp_b = tmp_b->next;
	}
}
/* get_target:
*	Picks the best target position in stack A for the given index of
*	an element in stack B. First checks if the index of the B element can
*	be placed somewhere in between elements in stack A, by checking whether
*	there is an element in stack A with a bigger index. If not, it finds the
*	element with the smallest index in A and assigns that as the target position.
*	--- Example:
*		target_pos starts at INT_MAX
*		B index: 3
*		A contains indexes: 9 4 2 1 0
*		9 > 3 && 9 < INT_MAX 	: target_pos updated to 9
*		4 > 3 && 4 < 9 			: target pos updated to 4
*		2 < 3 && 2 < 4			: no update!
*	So target_pos needs to be the position of index 4, since it is
*	the closest index.
*	--- Example:
*		target_pos starts at INT_MAX
*		B index: 20
*		A contains indexes: 16 4 3
*		16 < 20					: no update! target_pos = INT_MAX
*		4  < 20					: no update! target_pos = INT_MAX
*		3  < 20					: no update! target_pos = INT_MAX
*	... target_pos stays at INT MAX, need to switch strategies.
*		16 < 20					: target_pos updated to 20
*		4  < 20					: target_pos updated to 4
*		3  < 20					: target_pos updated to 3
*	So target_pos needs to be the position of index 3, since that is
*	the "end" of the stack.
*/