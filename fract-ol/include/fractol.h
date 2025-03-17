#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

# define X11_ESC 65307
# define close_window_button 17

typedef struct s_fractol
{
    void *mlx;
    void *win;
    void *img;
    char *name;
    char *addr;
    double zoom;
    double 
    int *bits_per_pixel;
    int *size_line;
    int *endian;
    int height;
    int width
    int color;
}   t_fractol;

//initialization
void mandelbrot_set(t_fractol *fractol, char *name);
void julia(t_fractol *fractol, char *name);


