/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:19 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 20:26:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
    int             id;
    long long       last_meal;
    int             eat_count;
    pthread_t       thread;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_rule   *rule;
}   t_philo;

typedef struct s_rule
{
    int             n_philo;
    long long       t_die;
    long long       t_eat;
    long long       t_sleep;
    int             must_eat;
    long long       start_time;
    volatile int    finish;
    pthread_mutex_t finish_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    t_philo         *philos;
    pthread_t       monitor_thread;
}   t_rule;

/*utilities */
long long   get_time_ms(void);
long long   ft_atoll(const char *str);

/* initialization */
t_rule      *init_rule(int ac, char **av);
void        init_philos(t_rule *rule);

/* threading */
int is_finish(t_rule *r);
void set_finish(t_rule *r);
int         create_threads(t_rule *rule);
void        join_threads(t_rule *rule);
void        *monitor_routine(void *arg);
void        *philo_routine(void *arg);
int finish_cheack(t_rule *rule);
void        handle_single_philo(t_philo *ph, t_rule *rule);
void        take_forks(t_philo *ph, t_rule *rule);
int eat(t_philo *ph, t_rule *rule);
void sleep_and_think(t_philo *ph, t_rule *rule);
void smart_sleep(long long ms);
int check_philo_death(t_rule *rule, int i);
int check_all_philos_done(t_rule *rule);

/* cleanup */
void        cleanup_rule(t_rule *rule);


#endif
