/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:02:07 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/26 18:06:30 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double change_plus(double i)
{
	if(i < 0)
		return (i * -1);
	return (i);
}

static double	parse_integer_part(char *str, int *i)
{
	double	integer_part;

	integer_part = 0.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		integer_part = integer_part * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (integer_part);
}

static double	parse_fractional_part(char *str, int *i)
{
	double	fractional_part;

	fractional_part = 0.0;
	if (str[*i] == '.')
		(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		fractional_part = fractional_part * 10 + (str[*i] - '0');
		(*i)++;
	}
	while (fractional_part >= 1)
		fractional_part /= 10;
	return (fractional_part);
}

double	ft_atof(char *str)
{
	double	integer_part;
	double	fractional_part;
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	integer_part = parse_integer_part(str, &i);
	fractional_part = parse_fractional_part(str, &i);
	return ((integer_part + fractional_part) * sign);
}
