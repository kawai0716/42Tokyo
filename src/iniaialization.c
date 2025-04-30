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

#include "Philosophers.h"

t_philos	*stack_new(int i)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_philos));
	if (!philo)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	philo->id = i;
	philo->eat_count = 0;
	philo->last_eat_time = 0;
	pthread_mutex_init(&philo->right_fork, NULL);
	pthread_mutex_init(&philo->left_fork, NULL);
	return (philos);
}

t_philos	*fill_stack(int ac, char **av)
{
	t_philo *philo;
	int i;

	i = 0;
	philos = NULL;
	while (i < ft_atoi(av[1]))
	{
		philos = stack_new(i);
		i++;
	}
	return (philos);
}
