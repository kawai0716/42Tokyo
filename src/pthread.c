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
int is_finished(t_rule *r)
{
    int f;
    pthread_mutex_lock(&r->finish_mutex);
    f = r->finish;
    pthread_mutex_unlock(&r->finish_mutex);
    return f;
}

/* finish フラグを安全に立てるヘルパー */
void set_finished(t_rule *r)
{
    pthread_mutex_lock(&r->finish_mutex);
    r->finish = 1;
    pthread_mutex_unlock(&r->finish_mutex);
}

static int all_satisfied(t_rule *r)
{
    if (r->must_eat < 0) return 0;
    for (int i = 0; i < r->n_philo; i++)
        if (r->philos[i].eat_count < r->must_eat)
            return 0;
    set_finished(r);
    return 1;
}

static int philosopher_died(t_rule *r)
{
    long long now = get_time_ms();
    for (int i = 0; i < r->n_philo; i++)
    {
        if (now - r->philos[i].last_eat_time > r->t_die)
        {
            set_finished(r);
            pthread_mutex_lock(&r->print);
            printf("%04lld %02d died\n",
                   now - r->start_ms, r->philos[i].id);
            pthread_mutex_unlock(&r->print);
            return 1;
        }
    }
    return 0;
}

void wait_for_completion(t_rule *r)
{
    while (1)
    {
        if (all_satisfied(r) || philosopher_died(r))
            break;
        usleep(1000);
    }
}

int create_threads(t_rule *r)
{
    for (int i = 0; i < r->n_philo; i++)
        if (pthread_create(&r->threads[i], NULL,
                           &routine, &r->philos[i]) != 0)
            return 0;
    return 1;
}

void detach_threads(t_rule *r)
{
    for (int i = 0; i < r->n_philo; i++)
        pthread_detach(r->threads[i]);
}
