/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:48:30 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/18 16:54:19 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+')
		;
	else if (*str == '-')
		b = -b;
	str++;
	while (*str >= '0' && *str <= '9')
	{
		a = a * 10 + (*str - '0');
		str++;
	}
	return (a * b);
}
// int main() {
//     int num = atoi("    ++1234");
//     printf("%d\n", num);
//     return (0);
// }
