/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:47 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/26 21:59:24 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mandelbrot_calculation(double cr, double ci)
{
	double	zr;
	double	zi;
	double	tmp;
	int		n;

	zr = 0;
	zi = 0;
	n = 0;
	while (zr * zr + zi * zi <= 4 && n < MAX_ITERATIONS)
	{
		tmp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = tmp;
		n++;
	}
	return (n);
}

void	mandelbrot_set(t_stack *fractol)
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
			n = mandelbrot_calculation(z.x, z.y);
			if (n == MAX_ITERATIONS)
				put_pixel(fractol, fractol->x, fractol->y, 0x000000);
			else
				put_pixel(fractol, fractol->x, fractol->y, fractol->color * n);
			fractol->y++;
		}
		fractol->x++;
	}
}
