#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

# define ESC 65307
# define right 65363
# define left 65361
# define up 65362
# define down 65364
# define plus 65451
# define minus 65453
# define scroll_up 4
# define scroll_down 5
# define
# define
# define close_window_button 17

typedef struct s_fractol
{
    void *mlx;
    void *win;
    void *img;
    char *name;
    char *addr;
    double zoom;
    double x;
    double y;
    double xarrow;
    double yarrow
    int bits_per_pixel;
    int size_line;
    int endian;
    int height;
    int width;
    int i;
    int color;
}   t_fractol;

//initialization
void mandelbrot_set(t_fractol *fractol, char *name);
void julia(t_fractol *fractol, char *name);


