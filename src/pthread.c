/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 05:10:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/12 05:10:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/* finish フラグを安全に読むヘルパー */
int is_finish(t_rule *r)
{
    int f;
    pthread_mutex_lock(&r->finish_mutex);
    f = r->finish;
    pthread_mutex_unlock(&r->finish_mutex);
    return (f);
}

/* finish フラグを安全に立てるヘルパー */
void set_finish(t_rule *r)
{
    pthread_mutex_lock(&r->finish_mutex);
    r->finish = 1;
    pthread_mutex_unlock(&r->finish_mutex);
}

void join_threads(t_rule *rule)
{
    int i;

    i = 0;
    while (i < rule->n_philo)
    {
        pthread_join(rule->philos[i].thread, NULL);
        i++;
    }
    pthread_join(rule->monitor_thread, NULL);
}

void cleanup_rule(t_rule *rule)
{
    int i;

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

int create_threads(t_rule *rule)
{
    int i;

    i = 0;
    while (i < rule->n_philo)
    {
        if (pthread_create(&rule->philos[i].thread, NULL,
                           philo_routine, &rule->philos[i]) != 0)
            return (0);
        i++;
    }
    if (pthread_create(&rule->monitor_thread, NULL,
                       monitor_routine, rule) != 0)
        return (0);
    return (1);
}