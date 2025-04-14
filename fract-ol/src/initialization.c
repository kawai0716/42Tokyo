/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:33 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/14 15:02:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_fractol *fractol, char *name)
{
	fractol->name = name;
	fractol->color = 0xE6CCFF;
	fractol->width = 1280;
	fractol->height = 720;
	fractol->zoom = 1;
	fractol->x = 0;
	fractol->y = 0;
	fractol->xarrow = 0;
	fractol->yarrow = 0;
	fractol->;
	fractol->;
}
void	julia(t_fractol *fractol, char *name)
{
	fractol->name = name;
	fractol->color = 0xE6CCFF;
	fractol->width = 1280;
	fractol->height = 720;
	fractol->zoom = 1;
	fractol->;
	fractol->;
	fractol->;
}
