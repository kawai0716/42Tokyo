/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:58:37 by syuto             #+#    #+#             */
/*   Updated: 2024/05/03 21:47:23 by sykawai          ###   ########.fr       */
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
		k = -k;
	while (k >= 10)
	{
		k /= 10;
		len++;
	}
	return (len);
}

char	*itoa_new(long *k, int j)
{
	char	*i;
	int		s;

	if (*k >= 0)
	i = (char *)malloc(sizeof(char) * (j + 1));
	s = 1;
	if (!i)
		return (NULL);
	if (*k < 0)
	{
		s = -1;
		*k = -(*k);
	}
	i[j--] = '\0';
	while (j >= 0)
	{
		i[j--] = (*k % 10) + '0';
		*k /= 10;
	}
	if (s < 0)
	{
		ft_memmove(i + 1, i, ft_strlen(i) + 1);
		i[0] = '-';
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		j;
	long	k;

	j = ft_numlen(n);
	k = n;
	return (itoa_new(&k, j));
}
