/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 05:10:33 by marvin            #+#    #+#             */
/*   Updated: 2025/05/12 05:10:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void smart_sleep(long long ms)
{
    long long start = get_time_ms();
    while (get_time_ms() - start < ms)
        usleep(100);
}

void *monitor_routine(void *arg)
{
    int     i;
    t_rule *rule;

    rule = (t_rule *)arg;
    while (1)
    {
        i = 0;
        while (i < rule->n_philo)
        {
            if (check_philo_death(rule, i))
                return (NULL);
            i++;
        }
        if (rule->must_eat > 0 && check_all_philos_done(rule))
            return (NULL);
        usleep(1000);
    }
}

void *philo_routine(void *arg)
{
    t_philo *ph;
    t_rule  *rule;

    ph = (t_philo *)arg;
    rule = ph->rule;
    if (rule->n_philo == 1)
    {
        handle_single_philo(ph, rule);
        return (NULL);
    }
    if (ph->id % 2)
        usleep(100);

    while (1)
    {
        if(!finish_cheack(rule))
            break;
        take_forks(ph, rule);
        if(!eat(ph, rule))
            break;
        sleep_and_think(ph, rule);
    }
    return  (NULL);
}
