/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:30 by sykawai           #+#    #+#             */
/*   Updated: 2025/05/24 18:26:59 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	safe_print(t_rule *rule, long long ts, int id, const char *msg)
{
	pthread_mutex_lock(&rule->finish_mutex);
	if (rule->finish)
	{
		pthread_mutex_unlock(&rule->finish_mutex);
		return ;
	}
	pthread_mutex_unlock(&rule->finish_mutex);
	pthread_mutex_lock(&rule->print_mutex);
	printf("%04lld %02d %s\n", ts, id, msg);
	pthread_mutex_unlock(&rule->print_mutex);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
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
