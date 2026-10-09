/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:46:34 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/26 21:53:45 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	mappoint(int x, int y, t_stack *fractol)
{
	t_complex	c;
	double		i;

	if (fractol->width > fractol->height)
		i = fractol->width * fractol->zoom;
	else
		i = fractol->height * fractol->zoom;
	x += fractol->xarrow;
	y += fractol->yarrow;
	c.x = 2 * fractol->radius * (x - fractol->width / 2) / i;
	c.y = 2 * fractol->radius * (y - fractol->height / 2) / i;
	return (c);
}

void	put_pixel(t_stack *fractol, int x, int y, int color)
{
	char	*dst;

	dst = fractol->addr + (y * fractol->size_line + x * (fractol->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}
