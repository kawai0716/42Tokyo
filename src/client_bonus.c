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

int main(int ac, char **av)
{
	pid_t pid;
	char message;
    if(ac != 3)
    	{
      		printf("Usage: %s <pid> <message>\n", av[0]));
			exit(EXIT_FAILURE);
    	}
	pid = ft_atoi(av[1]);
	message = av[2];
	
}
