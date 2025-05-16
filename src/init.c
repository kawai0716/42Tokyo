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

t_rule *set_rule(int ac, char **av)
{
    t_rule *rule;
    int     i;

    rule = malloc(sizeof(t_rule));
    if (!rule)
    {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    /* パラメータ読み込み */
    rule->n_philo  = ft_atoi(av[1]);
    rule->t_die    = ft_atoi(av[2]);
    rule->t_eat    = ft_atoi(av[3]);
    rule->t_sleep  = ft_atoi(av[4]);
    rule->must_eat = (ac == 6) ? ft_atoi(av[5]) : -1;

    /* 内部カウンタ初期化 */
    rule->start_ms = get_time_ms();
    atomic_store(&rule->finish, 0);
    rule->n_eat    = 0;
	rule->finish   = 0;

    /* 動的配列確保 */
    rule->forks   = malloc(sizeof(pthread_mutex_t) * rule->n_philo);
    rule->philos  = malloc(sizeof(t_philo)         * rule->n_philo);
    rule->threads = malloc(sizeof(pthread_t)       * rule->n_philo);
    if (!rule->forks || !rule->philos || !rule->threads)
    {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
	/* ミューテックス初期化 */
    pthread_mutex_init(&rule->print,     NULL);
	pthread_mutex_init(&rule->finish_mutex, NULL);
    pthread_mutex_init(&rule->eat_mutex, NULL);
    for (i = 0; i < rule->n_philo; i++)
        pthread_mutex_init(&rule->forks[i], NULL);

    return rule;
}

void fill_stack(t_rule *rule)
{
    int i;

	i = 0;
    while(i < rule->n_philo)
    {
        rule->philos[i].id            = i + 1;
        rule->philos[i].eat_count     = 0;
        rule->philos[i].last_eat_time = rule->start_ms;
        rule->philos[i].rule          = rule;
		i++;
    }
}