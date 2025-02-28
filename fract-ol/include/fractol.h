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