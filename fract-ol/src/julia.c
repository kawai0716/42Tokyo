#include "fractol.h"

t_complex mappoint(int x, int y, t_stack *fractol)
{
    
}

void julia_set(t_stack *fractol)
{
    int x;
    int y;
    int n;
    t_complex z;
    t_complex c;

    x = 0;
    while (fractol->width > x)
    {
        y = 0;
        while (fractol->height > y)
        {
            z = mappoint(x, y, fractol);
            y++; 
        }
        x++;
    }
}