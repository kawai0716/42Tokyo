/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:12 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 18:09:45 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	a(int signal)
{
	static char	c = 0;
	static int	bit_count = 0;

	if (signal == SIGUSR1)
		c |= 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", c);
		bit_count = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, a);
	signal(SIGUSR2, a);
	while (1)
		pause();
	return (0);
}
