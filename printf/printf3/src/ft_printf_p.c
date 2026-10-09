/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:07:19 by syuto             #+#    #+#             */
/*   Updated: 2024/06/14 21:21:24 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_p(void *p, int *n)
{
	unsigned long int	addr;

	if (!p)
		*n += write(1, "0x0", 3);
	else
	{
		addr = (unsigned long int)p;
		*n += write(1, "0x", 2);
		ft_printf_x3(addr, n);
	}
	return (*n);
}
