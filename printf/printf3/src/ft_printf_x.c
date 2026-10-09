/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:07:24 by syuto             #+#    #+#             */
/*   Updated: 2024/06/14 20:47:24 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_x(unsigned int i, int *n)
{
	char	*hex_digits;

	hex_digits = "0123456789abcdef";
	if (i >= 16)
		ft_printf_x(i / 16, n);
	*n += write(1, &hex_digits[i % 16], 1);
	return (*n);
}
