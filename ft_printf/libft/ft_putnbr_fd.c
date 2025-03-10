/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:18:59 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/28 13:33:30 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			digit;
	unsigned int	nb;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -1;
	}
	nb = n * sign;
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		digit = nb % 10 + '0';
		ft_putchar_fd(digit, fd);
	}
	else
	{
		digit = nb + '0';
		ft_putchar_fd(digit, fd);
	}
}
