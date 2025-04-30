/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iniaialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:42:59 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 19:39:04 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

t_philos	*stack_new(int i)
{
	t_philos	*philos;

	philos = malloc(sizeof(t_philos));
	if (!philos)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	philos->id = i;
	philos->eat_count = 0;
	philos->last_eat_time = 0;
	pthread_mutex_init(&philos->right_fork, NULL);
	pthread_mutex_init(&philos->left_fork, NULL);
	return (philos);
}

t_philos	*fill_stack(int ac, char **av)
{
	t_philos *philos;
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
