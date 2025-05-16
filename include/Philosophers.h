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
# include <stdatomic.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo t_philo;

typedef struct s_rule
{
    int             n_philo;
    long long            t_die;
    long long            t_eat;
    long long            t_sleep;
    int             must_eat;
    pthread_mutex_t    eat_mutex;
    int             n_eat;
    long long int            start_ms;
    volatile int    finish;
    pthread_mutex_t print;
    pthread_mutex_t finish_mutex;
    pthread_mutex_t *forks;
    pthread_t *threads;
    t_philo *philos;
}   t_rule;

typedef struct s_philo
{
    int             id;
    long long           last_eat_time;
    int             eat_count;
    t_rule          *rule;
}   t_philo;

long long get_time_ms(void);
t_rule *set_rule(int ac, char **av);
void fill_stack(t_rule *rule);
void detach_threads(t_rule *r);
void wait_for_completion(t_rule *r);
int create_threads(t_rule *r);
void set_finished(t_rule *r);
int is_finished(t_rule *r);
void pthread_action(t_philo *philo, t_rule *rule);
void *routine(void *av);
long long get_time_ms(void);
int check_number(char *av);
int ft_atoi(const char *str);

#endif
