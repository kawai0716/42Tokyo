/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:30 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/14 15:11:36 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_action(t_fractol *fractol)
{
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_image(fractol->mlx, fractol->img);
	free(fractol->addr);
	free(fractol);
	exit(0);
	return(0);
}

void	ft_zoom_in(double x, double y, t_fractol *fractol)
{
	fractol->x = (x / fractol->zoom) - (x / (fractol->zoom * 1.25));
	fractol->y = (y / fractol->zoom) - (y / (fractol->zoom * 1.25));
	fractol->zoom *= 1.25;
}

void	ft_zoom_out(double x, double y, t_fractol *fractol)
{
	fractol->x = (x / fractol->zoom) - (x / (fractol->zoom / 1.25));
	fractol->y = (y / fractol->zoom) - (y / (fractol->zoom / 1.25));
	fractol->zoom /= 1.25;
}

int	key_action(int keycode, t_fractol *fractol)
{
	if (keycode == ESC)
		close_action(fractol);
	else if (keycode == UP)
		fractol->yarrow -= 30;
	else if (keycode == DOWM)
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

int	mouse_action(int keycode, int x, int y, t_fractol *fractol)
{
	double	mouse_x;
	double	mouse_y;

	mouse_x = ((double)x - fractol->width / 2);
	mouse_y = ((double)y - fractol->height / 2);
	if (keycode == SCROLL_UP)
		ft_zoom_in(mouse_x, mouse_y, fractol);
	else if (keycode == SCROLL_DOWM)
		ft_zoom_out(mouse_x, mouse_y, fractol);
	fractol_update(fractol);
	return (0);
}
