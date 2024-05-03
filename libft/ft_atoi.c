/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:48:30 by sykawai           #+#    #+#             */
/*   Updated: 2024/05/03 18:26:23 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_overflow(long r, int j)
{
	if (r > 0)
	{
		if ((LONG_MAX - j) / 10 < r)
			return (1);
	}
	if (r < 0)
	{
		if ((LONG_MIN - j) / 10 > r)
			return (1);
	}
	return (0);
}

int	long_min_max(long i)
{
	if (i > 0)
		return ((int)LONG_MAX);
	else
		return ((int)LONG_MIN);
}

long	str_n(const char *str, int *i)
{
	long	r;
	int		j;

	r = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*i = -(*i);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		j = (*str - '0') * (*i);
		if (is_overflow(r, j))
			return (long_min_max(r));
		r = r * 10 + j;
		str++;
	}
	return (r);
}

int	ft_atoi(const char *str)
{
	int	i;

	i = 1;
	return (str_n(str, &i));
}
