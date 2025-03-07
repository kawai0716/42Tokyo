#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft"
#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

typedef struct s_fractol
{
    void *mlx;
    void *win;
    void *img;
    char *name;
    double zoom;
    double 
    int color;
}   t_fractol;

//initialization
void mandelbrot_set(t_fractol *fractol, char *name);
void julia(t_fractol *fractol, char *name);


