/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_di.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:07:08 by syuto             #+#    #+#             */
/*   Updated: 2024/06/14 20:20:49 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_di(int i, int *n)
{
	char			*decimal;
	unsigned int	nb;
	int				sign;

	decimal = "0123456789";
	sign = 1;
	if (i == -2147483648)
	{
		*n += write(1, "-2147483648", 11);
		return (*n);
	}
	if (i < 0)
	{
		*n += ft_putchar2('-');
		sign = -1;
	}
	nb = i * sign;
	if (nb >= 10)
		ft_printf_di(nb / 10, n);
	*n += write(1, &decimal[nb % 10], 1);
	return (*n);
}
