#include "philosophers.h"

void *routine(void *av)
{
	t_philo *philo;
	t_rule	*rule;

	philo = (t_philo *)av;
	rule = philo->rule;
	while(1)
	{       
        pthread_mutex_lock(philo->left);
        printf("%04lld %02d\e[1;33m has taken fork[%02d]\e[0m\n",
            timestamp_in_ms() - rule->start_ms, philo->id, philo->id);      
        pthread_mutex_lock(philo->right);
        printf("%04lld %02d\e[1;33m has taken fork[%02d]\e[0m\n",
            timestamp_in_ms() - rule->start_ms, philo->id, (philo->id + 1) % rule->n_philo);  
        printf("%04lld %02d\e[1;34m is eating\e[0m\n",
            timestamp_in_ms() - rule->start_ms, philo->id);
        usleep(rule->t_eat * 1000);
        philo->last_meal = timestamp_in_ms() - rule->start_ms;
        pthread_mutex_unlock(philo->left);
        pthread_mutex_unlock(philo->right);
        philo->eat_cnt++;
        if (philo->eat_cnt == rule->must_eat)
            rule->finish++;
        printf("%04lld %02d\e[1;34m is sleeping\e[0m\n",
            timestamp_in_ms() - rule->start_ms, philo->id);
        usleep(rule->t_sleep * 1000);
            printf("%04lld %02d\e[1;32m is thinking\e[0m\n",    
                timestamp_in_ms() - rule->start_ms, philo->id);
        
	}
}
