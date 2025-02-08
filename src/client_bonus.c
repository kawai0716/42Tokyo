/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:05 by marvin            #+#    #+#             */
/*   Updated: 2024/12/15 01:00:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void send_to_server(char message, int pid)
{
	int i;
	i = 7;
	while(i > 0)
	{
		if(message & (0×01 << i))
			kill(SIGUSR1,pid);
		else
			kill(SIGUSR2,pid);
		i--;
		usleep(42);
	}
}

void a(int signal)
{
	if(signal == SIGUSR1)
		ft_printf();
	else
		ft_printf();
}

int main(int ac, char **av)
{
	pid_t pid;
	char message;
	int i;
	signal(SIGUSR1,a);
	signal(SIGUSR2,a);
    if(ac != 3)
    {
  		printf("Usage: %s <pid> <message>\n", av[0]));
		exit(EXIT_FAILURE);
    }
	pid = ft_atoi(av[1]);
	message = av[2];
	i = 0;
	while(message[i])
	{
		send_to_server(message[i],pid)
		i++;	
	}
	send_to_server('\0',pid);
	return (0);
}
