/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:05 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 18:49:58 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_to_server(unsigned char message, int pid)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (message & (0x01 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(420);
	}
}

void	a(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("OK\n");
	else
		ft_printf("OK\n");
}

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*message;
	int		i;

	signal(SIGUSR1, a);
	signal(SIGUSR2, a);
	if (ac != 3)
		exit(1);
	pid = ft_atoi(av[1]);
	message = av[2];
	i = 0;
	while (message[i])
	{
		send_to_server(message[i], pid);
			i++;
	}
	send_to_server('\0', pid);
	return (0);
}
