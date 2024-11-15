void ft_putchr(char *s)
{
	while(*s)
	{
		write(1, s, 1);
		s++;
	}
}
