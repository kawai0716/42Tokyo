/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 05:10:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/23 14:32:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_threads(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->n_philo)
	{
		pthread_join(rule->philos[i].thread, NULL);
		i++;
	}
	pthread_join(rule->monitor_thread, NULL);
}

void	cleanup_rule(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->n_philo)
	{
		pthread_mutex_destroy(&rule->forks[i]);
		pthread_mutex_destroy(&rule->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&rule->finish_mutex);
	pthread_mutex_destroy(&rule->print_mutex);
	free(rule->forks);
	free(rule->philos);
	free(rule);
}

int	create_threads(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->n_philo)
	{
		if (pthread_create(&rule->philos[i].thread, NULL, philo_routine,
				&rule->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&rule->monitor_thread, NULL, monitor_routine, rule) != 0)
		return (0);
	return (1);
}
