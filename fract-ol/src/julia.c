/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:37 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/14 15:02:39 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia_set(t_stack *fractol)
{
	int x;
	int y;
	int n;
	double ci;
	double cr;

	x = 0;
	while (fractol->width > x)
	{
		y = 0;
		while (fractol->height > y)
		{
			y++;
		}
		x++;
	}
}