#include "fractol.h"
int key_action(int keycode, t_fractol *fractol)
{
    if(keycode == ESC)
        close_game(fractol);
    else if(keycode == up)  
        fractol-> y += 
    else if(keycode == down)
        fractol-> y -= 
    else if(keycode == right)
        fractol -> x += 
    else if(keycode == left)
        fractol -> x = 
    else if(keycode == plus)
        fractol -> 
    else if(keycode == minus)
}

int mouse_action(int keycode, int x, int y, t_fractol *fractol)
{

}