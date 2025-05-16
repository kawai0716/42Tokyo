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

static void choose_forks(t_philo *p, int *f1, int *f2)
{
    int sit = p->id - 1;
    int cnt = p->rule->n_philo;
    int flag;

    if (sit % 2)
    {
        if (cnt % 2)
            flag = 0;
        else
            flag = 1;
    }
    else
    {
        if (cnt % 2)
            flag = 1;
        else
            flag = 0;
    }
    if (flag)
    {
        *f1 = (sit + 1) % cnt;
        *f2 = sit;
    }
    else
    {
        *f1 = sit;
        *f2 = (sit + 1) % cnt;
    }
}

void precise_sleep(long long duration_ms)
{
    long long start = get_time_ms();
    while (1)
    {
        long long elapsed = get_time_ms() - start;
        if (elapsed >= duration_ms)
            break;
        long long remaining = duration_ms - elapsed;
        if (remaining > 5)
        {
            // 残りが多いときは 1ms ずつ粗取り
            usleep(1000);
        }
        //ビジーループ
    }
}

static void log_fork(t_philo *p, int fork_idx)
{
    t_rule     *r  = p->rule;
    pthread_mutex_lock(&r->print);
    if (!r->finish)
    {
        long long ts = get_time_ms() - r->start_ms;
        printf("%04lld %02d has taken fork[%02d]\n",
               ts, p->id, fork_idx);
    }
    pthread_mutex_unlock(&r->print);
}

static void log_eat(t_philo *p)
{
    t_rule     *r  = p->rule;

    pthread_mutex_lock(&r->print);
    if (!r->finish)
    {
        long long ts = get_time_ms() - r->start_ms;
        printf("%04lld %02d is eating\n",
               ts, p->id);
    }
    pthread_mutex_unlock(&r->print);
    precise_sleep(r->t_eat);
}

static void log_sleep(t_philo *p)
{
    t_rule     *r  = p->rule;

    pthread_mutex_lock(&r->print);
    if (!r->finish)
    {
        long long ts = get_time_ms() - r->start_ms;
        printf("%04lld %02d is sleeping\n",
               ts, p->id);
    }
    pthread_mutex_unlock(&r->print);
    precise_sleep(r->t_sleep);
}

static void log_think(t_philo *p)
{
    t_rule     *r  = p->rule;
    pthread_mutex_lock(&r->print);
    if (!r->finish)
    {
        long long ts = get_time_ms() - r->start_ms;
        printf("%04lld %02d is thinking\n",
               ts, p->id);
    }
    pthread_mutex_unlock(&r->print);
}

void *routine(void *arg)
{
    t_philo *philo   = arg;
    t_rule  *rule    = philo->rule;
    int       f1, f2;

    /* 哲学者１人だけのケース */
    if (rule->n_philo == 1)
    {
        pthread_mutex_lock(&rule->forks[0]);
        log_fork(philo, 0);
        pthread_mutex_unlock(&rule->forks[0]);
        usleep(rule->t_die * 1000);
        return NULL;
    }

    if (philo->id % 2 == 0)
        usleep(1);

    while (!is_finished(rule))
    {
        /* ─── フォークを選ぶ ─── */
        choose_forks(philo, &f1, &f2);

        /* ─── フォークを取る ─── */
        pthread_mutex_lock(&rule->forks[f1]);
        log_fork(philo, f1);
        pthread_mutex_lock(&rule->forks[f2]);
        log_fork(philo, f2);

        /* ─── 食事 ─── */
        philo->last_eat_time = get_time_ms();
        philo->eat_count++;
        log_eat(philo);

        /* ─── フォークを返す ─── */
        pthread_mutex_unlock(&rule->forks[f2]);
        pthread_mutex_unlock(&rule->forks[f1]);

        /* ─── must_eat 判定 ─── */
        if (rule->must_eat > 0 && philo->eat_count == rule->must_eat)
        {
            pthread_mutex_lock(&rule->eat_mutex);
            rule->n_eat++;
            if (rule->n_eat == rule->n_philo)
                set_finished(rule);
            pthread_mutex_unlock(&rule->eat_mutex);
            break;
        }

        /* ─── 睡眠 → 思考 ─── */
        log_sleep(philo);
        log_think(philo);
    }
    return (NULL);
}
