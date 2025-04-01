#include "fractol.h"

void ft_zoom(double x, double y, t_fractol *fractol)
{
    
}

int key_action(int keycode, t_fractol *fractol)
{
    if(keycode == ESC)
        close_game(fractol);
    else if(keycode == up)  
        fractol-> yarrow -= 30;
    else if(keycode == down)
        fractol-> yarrow += 30;
    else if(keycode == right)
        fractol -> xarrow += 30;
    else if(keycode == left)
        fractol -> xarrow -= 30;
    else if(keycode == plus)
        fractol -> color += 100;
    else if(keycode == minus)
        fractol -> color -= 100;
    if(keycode != ESC)
        fractol_update(fractol);
    return(0);
}

int mouse_action(int keycode, int x, int y, t_fractol *fractol)
{
    double mouse_x = ((double)x - fractol->width / 2);
    double mouse_y = ((double)y - fractol->height / 2);

    if(keycode == scroll_up)
        ft_zoom(mouse_x, mouse_y, fractol);
    else if(keycode == scroll_down)
        ft_zoom(mouse_x, mouse_y, fractol);
    fractol_update(fractol);
    return(0);
}
