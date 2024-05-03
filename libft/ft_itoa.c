/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:58:37 by syuto             #+#    #+#             */
/*   Updated: 2024/05/03 17:45:51 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int n)
{
	int		len;
	long	k;

	len = 1;
	k = n;
	if (k < 0)
	{
		k = -1 * k;
		len++;
	}
	while (k >= 10)
	{
		k /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		j;
	int		l;
	long	k;
	char	*i;

	j = ft_numlen(n);
	l = 0;
	i = (char *)malloc(sizeof(char) * (j + 1));
	if (!i)
		return (NULL);
	i[j--] = '\0';
	k = n;
	if (n < 0)
	{
		i[0] = '-';
		k = -k;
	}
	else
		k = n;
	if (k == 0)
	{
		i[j] = '0';
		return (i);
	}
	while (k > 0)
	{
		i[j] = k % 10 + '0';
		k /= 10;
		j--;
	}
	return (i);
}
