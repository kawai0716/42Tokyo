/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:20 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/24 18:15:13 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>

# define ESC 65307
# define RIGHT 65363
# define LEFT 65361
# define UP 65362
# define DOWN 65364
# define PLUS 65451
# define MINUS 65453
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define MAX_ITERATIONS 150
# define CLOSE_WINDOW_BUTTON 17
# define DESTROYNOTIFY 131072

typedef struct s_complex
{
	double		x;
	double		y;
}				t_complex;

typedef struct s_stack
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*name;
	char		*addr;
	double		zoom;
	double		x;
	double		y;
	double		xarrow;
	double		yarrow;
	double		radius;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			height;
	int			width;
	int			color;
	t_complex	c;
}				t_stack;

void			mandelbrot_set(t_stack *fractol);
void			julia_set(t_stack *fractol);
int				close_action(t_stack *fractol);
int				key_action(int keycode, t_stack *fractol);
int				mouse_action(int keycode, int x, int y, t_stack *fractol);
void			put_pixel(t_stack *fractol, int x, int y, int color);

#endif
