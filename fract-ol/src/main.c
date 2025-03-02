void fractol_check(char **av)
{
    char *tmp;

    tmp = av[1];
    if(!ft_strncmp(tmp, "mandelbrot", 10) && ft_strlen(tmp) == 10)
        mandelbrot;
    else if(!ft_strncmp(tmp, "julia", 5) && ft_strlen(tmp) == 5)
        julia;
    else if
}

int main(int ac,char **av)
{
    t_fractol fractol;

    if(ac==2 || ac==4)
    {
        fractol_check(av);
        
    }

    return(0);
}
