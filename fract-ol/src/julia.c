/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:37 by sykawai           #+#    #+#             */
/*   Updated: 2025/04/14 15:02:39 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex mappoint(int x, int y, t_stack *fractol)
{
	t_complex c;
	double i;
	
    if(fractol->width > fractol->height)
		i = fractol->width * fractol->zoom;
	else
		i = fractol->height * fractol->zoom;
	x+=fractol->xarrow;
	y+=fractol->yarrow;
	c.x = 2 * fractol->radius * (x-fractol->width/2) / i;
	c.y = 2 * fractol->radius * (y-fractol->height/2) / i;
	return (c);
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
