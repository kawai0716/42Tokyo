/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 05:49:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/24 19:18:40 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	finish_cheack(t_rule *rule)
{
	pthread_mutex_lock(&rule->finish_mutex);
	if (rule->finish)
	{
		pthread_mutex_unlock(&rule->finish_mutex);
		return (0);
	}
	pthread_mutex_unlock(&rule->finish_mutex);
	return (1);
}

void	handle_single_philo(t_philo *ph, t_rule *rule)
{
	pthread_mutex_lock(ph->left_fork);
	safe_print(rule, get_time_ms() - rule->start_time, ph->id,
		"has taken a fork");
	smart_sleep(rule->t_die);
	pthread_mutex_unlock(ph->left_fork);
}

void	take_forks(t_philo *ph, t_rule *rule)
{
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->right_fork);
		safe_print(rule, get_time_ms() - rule->start_time, ph->id,
			"has taken a fork");
		pthread_mutex_lock(ph->left_fork);
		safe_print(rule, get_time_ms() - rule->start_time, ph->id,
			"has taken a fork");
	}
	else
	{
		pthread_mutex_lock(ph->left_fork);
		safe_print(rule, get_time_ms() - rule->start_time, ph->id,
			"has taken a fork");
		pthread_mutex_lock(ph->right_fork);
		safe_print(rule, get_time_ms() - rule->start_time, ph->id,
			"has taken a fork");
	}
}

int	eat(t_philo *ph, t_rule *rule)
{
	pthread_mutex_lock(&ph->meal_mutex);
	ph->last_meal = get_time_ms();
	ph->eat_count++;
	pthread_mutex_unlock(&ph->meal_mutex);
	safe_print(rule, get_time_ms() - rule->start_time, ph->id, "is eating");
	smart_sleep(rule->t_eat);
	pthread_mutex_lock(&ph->meal_mutex);
	if (rule->must_eat > 0 && ph->eat_count >= rule->must_eat)
	{
		pthread_mutex_unlock(&ph->meal_mutex);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		return (0);
	}
	pthread_mutex_unlock(&ph->meal_mutex);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	return (1);
}

void	sleep_and_think(t_philo *ph, t_rule *rule)
{
	safe_print(rule, get_time_ms() - rule->start_time, ph->id, "is sleeping");
	smart_sleep(rule->t_sleep);
	safe_print(rule, get_time_ms() - rule->start_time, ph->id, "is thinking");
}
