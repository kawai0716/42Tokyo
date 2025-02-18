#include <stdio.h>
#include "include/ft_printf.h"

int main(void)
{
    // int value1, value2;
    // void *ptr = (void *)(long)ULONG_MAX;


    // value1 = printf("%p\n", ptr);
    // value2 = ft_printf("%p\n", ptr);

    // printf("printf returned: %d\n", value1);
    // printf("ft_printf returned: %d\n", value2);

    // return 0;

	char c = 'c';
	char *s = "abcd";
	int i = 2147483647;
	unsigned int u = 2147483647;

	printf("my ans = %d\n", ft_printf("c = %c, s = %s, p = %p, i = %i, d = %d, u = %u, x = %x, X = %X, %%\n", c, s, &s, i, i, u, u, u));
	printf("ans = %d\n", printf("c = %c, s = %s, p = %p, i = %i, d = %d, u = %u, x = %x, X = %X, %%\n", c, s, &s, i, i, u, u, u));


}
//ccw test.c libftprintf.a