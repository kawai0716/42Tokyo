/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 01:00:12 by marvin            #+#    #+#             */
/*   Updated: 2024/12/15 01:00:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void a(int signal)
{
    unsigned char c;
    int bit_count;
    
    if(signal == SIGUSR1)
        c |= 1;
    bit_count++;
    if(bit_count == 8)
    { 
        ft_printf("%d", c);
        bit_count = 0;
        c = 0;
    }
    else
        c <<= 1;
}
int main(void)
{
    printf("%d\n", getpid());
    signal(SIGUSR1, a);
    signal(SIGUSR2, a);
    while(1)
        pause();
    return(0);
}
