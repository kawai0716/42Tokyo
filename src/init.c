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

static t_rule *allocate_rule_resources(int n_philo)
{
    t_rule *rule = malloc(sizeof(t_rule));
    if (!rule)
    {
        printf("Error: malloc failed for rule\n");
        exit(1);
    }
    rule->forks = malloc(sizeof(pthread_mutex_t) * n_philo);
    rule->philos = malloc(sizeof(t_philo) * n_philo);
    if (!rule->forks || !rule->philos)
    {
        printf("Error: malloc failed for forks or philos\n");
        free(rule->forks);
        free(rule->philos);
        free(rule);
        exit(1);
    }
    return (rule);
}

t_rule *init_rule(int ac, char **av)
{
    int i;
    t_rule *rule;

    rule = allocate_rule_resources(atoll(av[1]));
    rule->n_philo = atoll(av[1]);
    rule->t_die = atoll(av[2]);
    rule->t_eat = atoll(av[3]);
    rule->t_sleep = atoll(av[4]);
    rule->must_eat = (ac == 6) ? atoll(av[5]) : -1;
    rule->start_time = get_time_ms();
    rule->finish = 0;

    pthread_mutex_init(&rule->finish_mutex, NULL);
    pthread_mutex_init(&rule->print_mutex, NULL);

    i = 0;
    while (i < rule->n_philo)
    {
        pthread_mutex_init(&rule->forks[i], NULL);
        i++;
    }
    return (rule);
}

void init_philos(t_rule *rule)
{
    int i;

    i = 0;
    while(i < rule->n_philo)
    {
        t_philo *ph = &rule->philos[i];
        ph->id       = i + 1;
        ph->last_meal = rule->start_time;
        ph->eat_count = 0;
        ph->left_fork = &rule->forks[i];
        ph->right_fork = &rule->forks[(i + 1) % rule->n_philo];
        ph->rule     = rule;
        pthread_mutex_init(&ph->meal_mutex, NULL);
        i++;
    }
}