void fractol_check(char **av, t_fractol fractol)
{
    char *tmp;

    tmp = av[1];
    if(!ft_strncmp(tmp, "mandelbrot", 10) && ft_strlen(tmp) == 10)
        mandelbrot_set(&fractol,av[1]);
    else if(!ft_strncmp(tmp, "julia", 5) && ft_strlen(tmp) == 5)
        julia_set(&fractol,av[1]);
    else if
}

int main(int ac,char **av)
{
    t_fractol fractol;

    if(ac==2 || ac==4)
    {
        fractol_check(av,fractol);
        
    }

    return(0);
}
