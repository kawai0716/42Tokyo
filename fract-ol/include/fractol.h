/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:20 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/14 15:09:25 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>

# define ESC 65307
# define RIGHT 65363
# define LEFT 65361
# define UP 65362
# define DOWM 65364
# define PLUS 65451
# define MINUS 65453
# define SCROLL_UP 4
# define SCROLL_DOWM 5
# define MAX_ITERATIONS 150
# define CLOSE_WINDOW_BUTTON 17

typedef struct s_fractol
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*name;
	char				*addr;
	double				zoom;
	double				x;
	double				y;
	double				xarrow;
	double yarrow int	bits_per_pixel;
	int					size_line;
	int					endian;
	int					height;
	int					width;
	int					color;
}						t_fractol;

//initialization
void					mandelbrot_set(t_fractol *fractol, char *name);
void					julia(t_fractol *fractol, char *name);
_WINDOW_BUTTON