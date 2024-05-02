/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:58:37 by syuto             #+#    #+#             */
/*   Updated: 2024/05/01 15:44:52 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_numlen(int n)
{
    int i = 1;
    if (n < 0)
        i++;
    while (n >= 10 || n <= -10)
    {
        n /= 10;
        i++;
    }
    return (i);
}

char *ft_itoa(int n)
{
    int j = ft_numlen(n);
    unsigned int k;
    char *i = (char *)malloc(sizeof(char) * (j + 1));
    if (!i)
        return NULL;
    i[j--] = '\0';
    if (n < 0)
    {
        i[0] = '-';
        k = -n;
    }
    else
    {
        k = n;
    }
    while (j >= 0)
    {
        i[j] = k % 10 + '0';
        k /= 10;
        j--;
    }
    return (i);
}
