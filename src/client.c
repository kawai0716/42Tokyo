/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:07 by marvin            #+#    #+#             */
/*   Updated: 2024/12/15 01:00:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//コマンドライン引数ではac = 2にはpidでac = 3には受信する文字
int main(int ac, char **av)
{
    pid_t pid;
    char *message;
    int i;

    message = av[2];
    i=0;
    if(av != 3)
    {
        ft_printf("Usage %s <PID> <MWSSAGE>\n", av[0])
        exit(EXIT_FAILURE)
    }
    pid = ft_atoi(av[1]);
    pid_error(pid);
    while(message[i])
        send_to_server(message[i], pid);
    send_to_server('\0',pid);
    return (0);    
}

void send_to_server(unsigned char c, int pid)
{
    int i;

    i = 7;
    while(i>0)
    {
        if((c & (0×01 << i)))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        i--;
        usleep(42);
    }
}

void pid_error(int pid)
{
    if(pid <= 0 || kill(pid, 0) == -1)
        {
            ft_printf("Inavalid PID\n");
            exit(EXIT_FAILURE);
        }
}
