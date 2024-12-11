/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:51:51 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/11 18:00:32 by sykawai          ###   ########.fr       */
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

void	ft_putchr(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

int	change_plus(int i)
{
	if (i < 0)
		return (i * -1);
	return (i);
}
