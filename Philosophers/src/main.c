/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:26 by sykawai           #+#    #+#             */
/*   Updated: 2025/07/01 17:07:24 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//./philo 5 800 200 200 (5) 引数は、何人、寿命、食事時間、睡眠時間、最大食事回数(ないなら無限ループ、あるなら制限付きループ)

static void	check_num_args(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Number of arguments\n");
		exit(1);
	}
}

static void	check_args(int ac, char **av)
{
	int	i;
	int	j;

	check_num_args(ac);
	if (ft_atoi(av[1]) <= 0 || (ac == 6 && ft_atoi(av[5]) <= 0))
	{
		printf("Error: number of philos and must_eat must be greater than 0\n");
		exit(1);
	}
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: invalid argument '%s'\n", av[i]);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_rule	*rule;

	check_args(ac, av);
	rule = init_rule(ac, av);
	init_philos(rule);
	if (!create_threads(rule))
	{
		printf("Error: pthread_create failed\n");
		cleanup_rule(rule);
		return (1);
	}
	join_threads(rule);
	cleanup_rule(rule);
	return (0);
}
