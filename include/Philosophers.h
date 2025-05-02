/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:41:19 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 20:26:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

tyepedef struct s_rule
{
}					t_rule;
typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_eat_time;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	t_rule 			*rule;
}					t_philo;