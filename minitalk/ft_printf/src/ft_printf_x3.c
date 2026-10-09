/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:11:16 by sykawai           #+#    #+#             */
/*   Updated: 2024/06/14 21:30:16 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_x3(unsigned long int i, int *n)
{
	char	*hex_digits;

	hex_digits = "0123456789abcdef";
	if (i >= 16)
		ft_printf_x3(i / 16, n);
	*n += write(1, &hex_digits[i % 16], 1);
	return (*n);
}
