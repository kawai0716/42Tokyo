/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:56:13 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 15:13:20 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	burning_ship_calculation(double cr, double ci)
{
	double	tmp;
	double	zr;
	double	zi;
	int		n;

	zr = 0;
	zi = 0;
	n = 0;
	while (zr * zr + zi * zi <= 4 && n < MAX_ITERATIONS)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = change_plus(2 * zr * zi) + ci;
		zr = tmp;
		n++;
	}
	return (n);
}

void	burning_ship_set(t_stack *fractol)
{
	int			n;
	t_complex	z;

	fractol->x = 0;
	while (fractol->width > fractol->x)
	{
		fractol->y = 0;
		while (fractol->height > fractol->y)
		{
			z = mappoint(fractol->x, fractol->y, fractol);
			n = burning_ship_calculation(z.x, z.y);
			if (n == MAX_ITERATIONS)
				put_pixel(fractol, fractol->x, fractol->y, 0x00000000);
			else
				put_pixel(fractol, fractol->x, fractol->y, fractol->color * n);
			fractol->y++;
		}
		fractol->x++;
	}
}