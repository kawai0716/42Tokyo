/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:07 by marvin            #+#    #+#             */
/*   Updated: 2025/02/18 19:49:25 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_to_server(unsigned char c, int pid)
{
	int	i;

	i = 7;
	while (i > 0)
	{
		if ((c & (0x01 << i)))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(420);
	}
}

void	pid_error(int pid)
{
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_printf("Inavalid PID\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*message;
	int		i;

	message = av[2];
	i = 0;
	if (ac != 3)
		exit(1);
	pid = ft_atoi(av[1]);
	pid_error(pid);
	while (message[i])
	{
		send_to_server(message[i], pid);
		i++;
	}
	send_to_server('\0', pid);
	return (0);
}
