/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniaialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:42:59 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 20:26:16 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*stack_new(int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * rule->n_philo);
	if (!philo)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	philo->id = i + 1;
	philo->eat_count = 0;
	philo->last_eat_time = rule->start_ms;
	philo->rule = rule;
	philo->left = &rule->forks[i];
	if (i + 1 == rule->n_philo)
		philo->right = &rule->forks[0];
	else
		philo->right = &rule->forks[i + 1];
	return (philo);
}

t_philo	*fill_stack(t_rule *rule)
{
	t_philo *philo;
	int i;

	i = 0;
	while (i < rule->n_philo)
	{
		philo[i] = stack_new(i);
		i++;
	}
	return (philo);
}
