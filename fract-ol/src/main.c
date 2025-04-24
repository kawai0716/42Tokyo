/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:41 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/24 18:16:40 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractol_update(t_stack *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img);
	fractol->img = mlx_new_image(fractol->mlx, fractol->width, fractol->height);
	fractol->addr = mlx_get_data_addr(fractol->mlx, &fractol->bits_per_pixel,
			&fractol->size_line, &fractol->endian);
	if (!ft_strncmp(fractol->name, "mandelbrot", 10))
		mandelbrot_set(fractol);
	else if (!ft_strncmp(fractol->name, "julia", 5))
		julia_set(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

void	fractol_check(int ac, char **av, t_stack *fractol)
{
	char	*tmp;
	double	real;
	double	imag;

	real = ft_atoi(av[2]);
	imag = ft_atoi(av[3]);
	tmp = av[1];
	if (!ft_strncmp(tmp, "mandelbrot", 10) && ft_strlen(tmp) == 10 && ac == 2)
		mandelbrot(fractol, av[1]);
	else if (!ft_strncmp(tmp, "julia", 5) && ft_strlen(tmp) == 5 && ac == 4)
		julia(fractol, av[1], real, imag);
}

int	main(int ac, char **av)
{
	t_stack	fractol;

	if (ac == 2 || ac == 4)
	{
		fractol_check(ac, av, &fractol);
		fractol.mlx = mlx_init();
		fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height,
				fractol.name);
		fractol.img = mlx_new_image(fractol.mlx, fractol.width, fractol.height);
		fractol_update(&fractol);
		mlx_key_hook(fractol.mlx, key_action, &fractol);
		mlx_mouse_hook(fractol.mlx, mouse_action, &fractol);
		mlx_hook(fractol.mlx, CLOSE_WINDOW_BUTTON, 1L << 17, close_action,
				&fractol);
		mlx_loop(fractol.mlx);
	}
	return (0);
}
