/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 06:10:32 by marvin            #+#    #+#             */
/*   Updated: 2025/05/24 18:04:12 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_death(t_rule *rule, int i)
{
	long long	last;

	pthread_mutex_lock(&rule->philos[i].meal_mutex);
	last = rule->philos[i].last_meal;
	pthread_mutex_unlock(&rule->philos[i].meal_mutex);
	if (get_time_ms() - last > rule->t_die)
	{
		pthread_mutex_lock(&rule->finish_mutex);
		rule->finish = 1;
		pthread_mutex_unlock(&rule->finish_mutex);
		pthread_mutex_lock(&rule->print_mutex);
		printf("%04lld %02d died\n", get_time_ms() - rule->start_time,
			rule->philos[i].id);
		pthread_mutex_unlock(&rule->print_mutex);
		return (1);
	}
	return (0);
}

int	check_all_philos_done(t_rule *rule)
{
	int	i;
	int	done;

	i = 0;
	done = 1;
	while (i < rule->n_philo)
	{
		pthread_mutex_lock(&rule->philos[i].meal_mutex);
		if (rule->philos[i].eat_count < rule->must_eat)
			done = 0;
		pthread_mutex_unlock(&rule->philos[i].meal_mutex);
		i++;
	}
	if (done)
	{
		pthread_mutex_lock(&rule->finish_mutex);
		rule->finish = 1;
		pthread_mutex_unlock(&rule->finish_mutex);
		return (1);
	}
	return (0);
}
