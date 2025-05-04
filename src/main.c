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
	t_philo *z;
	int i;

	if (ac == 5 || ac == 6)
	{
		chech_argument(ac, av);
		z = fill_satck(ac, av);
		i = ft_atoi(av[1]);
	}
	return(0);
}
