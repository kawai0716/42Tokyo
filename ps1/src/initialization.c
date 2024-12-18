/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:05:41 by marvin            #+#    #+#             */
/*   Updated: 2024/12/18 22:05:34 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*fill_stack2(int ac, char **av)
{
	long int	n;
	int			i;
	t_stack		*stack_a;

	n = 0;
	i = 0;
	stack_a = NULL;
	while (i < ac)
	{
		n = ft_atoi(av[i]);
		if (INT_MAX < n || n < INT_MIN)
		{
			free_split(av);
			exit_error(&stack_a, NULL);
		}
		if (i == 0)
			stack_a = stack_new((int)n);
		else
			stack_add_bottom(&stack_a, stack_new((int)n));
		i++;
	}
	return (stack_a);
}

t_stack	*fill_stack(int ac, char **av)
{
	long int	n;
	int			i;
	t_stack		*stack_a;

	n = 0;
	i = 1;
	stack_a = NULL;
	while (i < ac)
	{
		n = ft_atoi(av[i]);
		if (INT_MAX < n || n < INT_MIN)
		{
			if (ac == 2)
				free_split(av);
			exit_error(&stack_a, NULL);
		}
		if (i == 1)
			stack_a = stack_new((int)n);
		else
			stack_add_bottom(&stack_a, stack_new((int)n));
		i++;
	}
	return (stack_a);
}
