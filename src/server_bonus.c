/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:09 by marvin            #+#    #+#             */
/*   Updated: 2024/12/15 01:00:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void a(int signal, siginfo_t *info, void *context)
{
	unsigned char c;
	int bit_count;
	(void)context;

	bit_count = 0;
	c = NULL;
	if(signal == SIGUSR1)
		c |= 1;
	bit_count++;
	if(bit_count == 8)
	{
		printf("%s",c);
		c = 0;
		bit_count = 0;
	}
	else
		c <<= 1;
	if(signal == SIGUSR1)
		kill(info->si_pid,SIGUSR1);
	else if(signal == SIGUSR2)
		kill(info->si_pid,SIGUSR2)
}
int main(void)
{
	struct sigaction sa;
	sa.sa_handler = a;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1,&sa,NULL);
	sigaction(SIGUSR2,&sa,NULL);
	while(1)
		pause();
	return(0);
}
