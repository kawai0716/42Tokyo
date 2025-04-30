/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:30 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/30 15:28:22 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_action(t_stack *fractol)
{
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_image(fractol->mlx, fractol->img);
	exit(0);
	return (0);
}

static void	zoom_mouse(int x, int y, t_stack *fractol, double zoom_factor)
{
	double	dx;
	double	dy;

	dx = x - (fractol->width / 2.0);
	dy = y - (fractol->height / 2.0);
	fractol->xarrow = fractol->xarrow * zoom_factor + dx * (zoom_factor - 1.0);
	fractol->yarrow = fractol->yarrow * zoom_factor + dy * (zoom_factor - 1.0);
	fractol->zoom *= zoom_factor;
}

int	key_action(int keycode, t_stack *fractol)
{
	if (keycode == ESC)
		close_action(fractol);
	else if (keycode == UP)
		fractol->yarrow -= 30;
	else if (keycode == DOWN)
		fractol->yarrow += 30;
	else if (keycode == RIGHT)
		fractol->xarrow += 30;
	else if (keycode == LEFT)
		fractol->xarrow -= 30;
	else if (keycode == PLUS)
		fractol->color += 100;
	else if (keycode == MINUS)
		fractol->color -= 100;
	if (keycode != ESC)
		fractol_update(fractol);
	return (0);
}

int	mouse_action(int keycode, int x, int y, t_stack *fractol)
{
	if (keycode == SCROLL_UP)
		zoom_mouse(x, y, fractol, 1.3);
	else if (keycode == SCROLL_DOWN)
		zoom_mouse(x, y, fractol, 1 / 1.3);
	fractol_update(fractol);
	return (0);
}
