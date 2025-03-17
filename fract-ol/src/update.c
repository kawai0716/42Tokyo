void fractol_update(t_struct *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img);
	fractol->img = mlx_new_image(fractol->mlx, &fractol->bits_per_pixel, &fractol->size_line, &fractol->endian);
	fractol
}
