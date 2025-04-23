/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:47 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/14 15:03:04 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_stack *fractol, int x, int y, int color)
{
	char	*dst;

	dst = fractol->addr + (y * fractol->size_line + x * (fractol->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	mandelbrot(double cr, double ci, int i)
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
	int		x;
	int		y;
	int		n;
	double	cr;
	double	ci;

	x = 0;
	while (fractol->width > x)
	{
		y = 0;
		while (fractol->height > y)
		{
			cr = (x + fractol->xarrow) / fractol->zoom * (0.47 + 2.0)
				/ (fractol->width - 1) - 2.0;
			ci = (y + fractol->yarrow) / fractol->zoom * (1.12 + 1.12)
				/ (fractol->height - 1) - 1.12;
			n = mandelbrot(cr, ci);
			if (n == MAX_ITERATIONS)
				put_pixel(fractol, x, y, 0x000000);
			else
				put_pixel(fractol, x, y, fractol->color * n);
			y++;
		}
		x++;
	}
}
git add .
git commit -m "kawai"
git push