/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:26 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 20:25:52 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//./philo 5 800 200 200 (5) 引数は、何人寿命、食事時間、睡眠時間、最大食事回数(ないなら無限ループ、あるなら制限付きループ)

static void	check_argument(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
    {
        printf("Usage: %s philo_count t_die t_eat t_sleep [must_eat]\n", av[0]);
        exit(1);
    }
	while (i < ac)
	{
		if(!check_number(av[i]))
		{
			printf("Error: Argument is not a number.\n");
			exit(1);
		}
		if (ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > INT_MAX)
		{
			printf("Error: Argument %s is not a positive integer.\n", av[i]);
			exit(1);
		}
		i++;
	}
}

int main(int ac, char **av)
{
    t_rule *rule;
	int i;

    check_argument(ac, av);
    rule = set_rule(ac, av);
    fill_stack(rule);

    if (!create_threads(rule))
        exit(1);
    wait_for_completion(rule);
    detach_threads(rule);
    usleep(10000);
	i = 0;
	while (i < rule->n_philo)
	{
		pthread_mutex_destroy(&rule->forks[i]);
		i++;
	}
    pthread_mutex_destroy(&rule->print);
    pthread_mutex_destroy(&rule->eat_mutex);
	pthread_mutex_destroy(&rule->finish_mutex);
    free(rule->forks);
    free(rule->philos);
    free(rule->threads);
    free(rule);

    return (0);
}
