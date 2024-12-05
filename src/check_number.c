/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:19:06 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/05 19:25:59 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Push_swap.h"

static int	number(char *av)
{
	int	n;

	n = 0;
	if (ft_sign(av[n]) && av[n + 1])
		n++;
	while (ft_isdigit(av[n]) && av[n])
		n++;
	if (av[n] && !ft_isdigit(av[n]))
		return (0);
	return (1);
}

static int	zero_count(char *av)
{
	int	n;

	n = 0;
	if (ft_sign(av[n]) && av[n + 1])
		n++;
	while (av[n] && av[n] == '0')
		n++;
	if (av[n])
		return (0);
	return (1);
}

static int	doplicates(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 1;
		while (av[j])
		{
			if (i = !j && same_number(av[i], av[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_number(char **av)
{
	int n;
	int zero;

	n = 1;
	zero = 0;
	while (av[n])
	{
		if (!number(av[n]))
			return (0);
		zero += zero_count(av[n]);
		n++;
	}
	if (zero > 1)
		return (0);
	//重複文字があったら真である１を返すため！はいらない
	if (duplicates(av))
		return (0);
	return (1);
}