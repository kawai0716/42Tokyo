/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:37 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/26 21:46:53 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	julia_calculate(t_complex z, t_stack *fractol)
{
	int			n;
	t_complex	tmp;

	n = 0;
	while (z.x * z.x + z.y * z.y <= 4 && n < MAX_ITERATIONS)
	{
		tmp.x = z.x * z.x - z.y * z.y + fractol->c.x;
		tmp.y = 2 * z.x * z.y + fractol->c.y;
		z = tmp;
		n++;
	}
	return (n);
}

void	julia_set(t_stack *fractol)
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
			n = julia_calculate(z, fractol);
			if (n == MAX_ITERATIONS)
				put_pixel(fractol, fractol->x, fractol->y, 0x00000000);
			else
				put_pixel(fractol, fractol->x, fractol->y, fractol->color * n);
			fractol->y++;
		}
		fractol->x++;
	}
}

// void	julia_set(t_stack *fractol)
// {
// 	int			x;
// 	int			y;
// 	int			n;
// 	t_complex	z;
// 	t_complex	tmp;

// 	x = 0;
// 	while (fractol->width > x)
// 	{
// 		y = 0;
// 		while (fractol->height > y)
// 		{
// 			z = mappoint(x, y, fractol);
// 			n = 0;
// 			while (z.x * z.x + z.y * z.y <= 4 && n < MAX_ITERATIONS)
// 			{
// 				tmp.x = z.x * z.x - z.y * z.y + fractol->c.x;
// 				tmp.y = 2 * z.x * z.y + fractol->c.y;
// 				z = tmp;
// 				n++;
// 			}
// 			if (n == MAX_ITERATIONS)
// 				put_pixel(fractol, x, y, 0x00000000);
// 			else
// 				put_pixel(fractol, x, y, fractol->color * n);
// 			y++;
// 		}
// 		x++;
// 	}
// }
