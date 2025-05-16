/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:30 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 16:41:32 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long long get_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int check_number(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return(0);
		i++;
	}
	return(1);
}

int	ft_atoi(const char *str)
{
	int i = 0;
	int sign = 1;
	long result = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}