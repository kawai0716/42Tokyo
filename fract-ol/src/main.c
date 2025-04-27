/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:41 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/26 20:42:38 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractol_update(t_stack *fractol)
{
	if (fractol->img)
		mlx_destroy_image(fractol->mlx, fractol->img);
	fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
	fractol->addr = mlx_get_data_addr(fractol->img, &fractol->bits_per_pixel,
			&fractol->size_line, &fractol->endian);
	if (!ft_strncmp(fractol->name, "mandelbrot", 10))
		mandelbrot_set(fractol);
	else if (!ft_strncmp(fractol->name, "julia", 5))
		julia_set(fractol);
	else if (!ft_strncmp(fractol->name, "burningship", 11))
		burning_ship_set(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

static void	fractol_check(int ac, char **av, t_stack *fractol)
{
	char	*tmp;
	double	real;
	double	imag;

	tmp = av[1];
	if (!ft_strncmp(tmp, "mandelbrot", 10) && ft_strlen(tmp) == 10 && ac == 2)
		mandelbrot(fractol, av[1]);
	else if (!ft_strncmp(tmp, "julia", 5) && ft_strlen(tmp) == 5 && ac == 4)
	{
		real = ft_atof(av[2]);
		imag = ft_atof(av[3]);
		if ((real > 2.0 || real < -2.0) || (imag >= 2.0 || imag <= -2.0))
			exit(1);
		julia(fractol, av[1], real, imag);
	}
	else if (!ft_strncmp(tmp, "burningship", 11) && ft_strlen(tmp) == 11 && ac == 2)
		burning_ship(fractol, av[1]);
	else
		exit(1);
}

int	main(int ac, char **av)
{
	t_stack	fractol;

	fractol.img = NULL;
	if (ac == 2 || ac == 4)
	{
		fractol_check(ac, av, &fractol);
		fractol.mlx = mlx_init();
		fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height,
				fractol.name);
		fractol_update(&fractol);
		mlx_key_hook(fractol.win, key_action, &fractol);
		mlx_mouse_hook(fractol.win, mouse_action, &fractol);
		mlx_hook(fractol.win, CLOSE_WINDOW_BUTTON, DESTROYNOTIFY, close_action,
			&fractol);
		mlx_loop(fractol.mlx);
	}
	return (0);
}
