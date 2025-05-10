#include "philosophers.h"

void pthread_action(t_philo *philo, t_rule *rule)
{
    int i;

    i = 0;
    while (i < rule->n_philo)
    {
        pthread_create(&philo[i].th, NULL, &routine, &philo[i]);
        i++;
    }
    i = 0;
    while (i < rule->n_philo)
    {
        pthread_join(philo[i].th, NULL);
        i++;
    }
    i = 0;
    while (i < rule->n_philo)
    {
        pthread_mutex_destroy(&rule->forks[i]);
        i++;
    }
}