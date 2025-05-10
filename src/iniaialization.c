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

long get_tiem_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

t_rule *set_rule(int ac, char **av)
{
	t_rule	*rule;
	int i;

	rule = malloc(sizeof(t_rule));
	rule->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!rule || !rule->forks)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	rule->n_philo = ft_atoi(av[1]);
	rule->t_die = ft_atoi(av[2]);
	rule->t_eat = ft_atoi(av[3]);
	rule->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		rule->must_eat = ft_atoi(av[5]);
	else
		rule->must_eat = -1;
	rule->start_ms = get_tiem_ms();
	rule->finish = 0;
	i = 0;
	while(rule->n_philo > i)
		pthread_mutex_init(&rule->forks[i++], NULL);
	return (rule);
}

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
