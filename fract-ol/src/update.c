void fractol_update(t_struct *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img);
	fractol->img = mlx_new_image(fractol->mlx, &fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
	fractol->addr = mlx_get_data_addr(fractol->mlx, &fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
	if(!ft_strncmp(fractol->name, "mandelbrot", 10))
        mandelbrot_set(fractol);
    else if(!ft_strncmp(fractol->name, "julia", 5))
        julia_set(fractol);
	
}
