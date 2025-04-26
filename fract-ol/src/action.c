/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:30 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/26 21:44:15 by sykawai          ###   ########.fr       */
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
	t_complex	before;
	t_complex	after;

	before = mappoint(x, y, fractol);
	fractol->zoom *= zoom_factor;
	after = mappoint(x, y, fractol);
	fractol->xarrow += (before.x - after.x) * fractol->width;
	fractol->yarrow += (before.y - after.y) * fractol->height;
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
