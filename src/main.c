/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:26 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 20:25:52 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//./philo 5 800 200 200 (5) 引数は、何人寿命、食事時間、睡眠時間、最大食事回数(ないなら無限ループ、あるなら制限付きループ)
void *routine(void *av)
{
	t_philo *philo;
	t_rule	*rule;

	philo = (t_philo *)av;
	rule = philo->rule;
	while(1)
	{	
	}
	// スレッドのルーチン
	// 1. フォークを取る
	// 2. 食事する
	// 3. フォークを置く
	// 4. 寝る
	// 5. 起きる
	// 6. 終了する
}

long get_tiem_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

t_rule *set_rule(int ac, char **av)
{
	t_rule	*rule;
	int i;

	rule = malloc(sizeof(t_rule));
	rule->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!rule || !rule->forks)
	{
		printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	rule->n_philo = ft_atoi(av[1]);
	rule->t_die = ft_atoi(av[2]);
	rule->t_eat = ft_atoi(av[3]);
	rule->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		rule->must_eat = ft_atoi(av[5]);
	else
		rule->must_eat = -1;
	rule->start_ms = get_tiem_ms();
	rule->finish = 0;
	phtread_mutex_init(&rule->print, NULL);
	i = 0;
	while(rule->n_philo > i)
		pthread_mutex_init(&rule->forks[i++], NULL);
	return (rule);
}

void	chech_argument(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if(!check_number(av[i]))
		{
			printf("Error: Argument is not a number.\n");
			exit(1);
		}
		if (ft_atoi(av[i]) <= 0 && ft_atoi(av[i]) > INT_MAX)
		{
			printf("Error: Argument %s is not a positive integer.\n", av[i]);
			exit(1);
		}
		i++;
	}
	return(1);
}

int	main(int ac, char **av)
{
	t_philo *philo;
	t_rule	*rule;
	int i;

	if (ac == 5 || ac == 6)
	{
		chech_argument(ac, av);
		rule = set_rule(ac, av);
		philo = fill_satck(rule);

	}
	return(0);
}
