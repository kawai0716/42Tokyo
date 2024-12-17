/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:05:09 by marvin            #+#    #+#             */
/*   Updated: 2024/12/17 15:44:56 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	number(char *av)
{
	int	i;

	i = 0;
	if (ft_sign(av[i]) && av[i + 1])
		i++;
	while (av[i] && ft_isdigit(av[i]))
		i++;
	if (av[i] && !ft_isdigit(av[i]))
		return (0);
	return (1);
}

static int	duplicates(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 1;
		while (av[j])
		{
			if (j != i && same_number(av[i], av[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	zero_count(char *av)
{
	int	i;

	i = 0;
	if (ft_sign(av[i]))
		i++;
	while (av[i] && av[i] == '0')
		i++;
	if (av[i] != '\0')
		return (0);
	return (1);
}

int	check_number(char **av)
{
	int	i;
	int	zero;

	zero = 0;
	i = 1;
	while (av[i])
	{
		if (!number(av[i]))
			return (0);
		zero += zero_count(av[i]);
		i++;
	}
	if (zero > 1)
		return (0);
	if (duplicates(av))
		return (0);
	return (1);
}