#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

tyepedef struct s_rule
{
    
} t_rule;
typedef struct s_philo
{
    int             id;
    int             eat_count;
    long            last_eat_time;
    pthread_mutex_t      right_fork;
    pthread_mutex_t      left_fork;
    t_rule *rule    t_philo;
} t_philo;