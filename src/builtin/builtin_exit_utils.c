/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:33:56 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/06 09:33:56 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_overflow(long result, int digit, int sign)
{
	if (sign > 0)
	{
		if (result > LONG_MAX / 10)
			return (1);
		if (result == LONG_MAX / 10 && digit > LONG_MAX % 10)
			return (1);
	}
	else
	{
		if (result > -(LONG_MIN / 10))
			return (1);
		if (result == -(LONG_MIN / 10) && digit > -(LONG_MIN % 10))
			return (1);
	}
	return (0);
}

static int	parse_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long	custom_atol(char *str, int *overflow)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	i = 0;
	*overflow = 0;
	sign = parse_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(result, str[i] - '0', sign))
		{
			*overflow = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
