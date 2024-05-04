/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 22:58:37 by syuto             #+#    #+#             */
/*   Updated: 2024/05/04 12:34:41 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_numlen(long n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n >= 1)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char		*ft_itoa_new(char *s, long k, int len, int i)
{
	if (k != 0)
		s = malloc(sizeof(char) * (len + 1));
	else
		return (s = ft_strdup("0"));
	if (!s)
		return (0);
	i = 0;
	if (k < 0)
	{
		i++;
		k = -k;
	}
	s[len] = '\0';
	while (--len)
	{
		s[len] = (k % 10) + '0';
		k /= 10;
	}
	if (i == 1)
		s[0] = '-';
	else
		s[0] = (k % 10) + '0';
	return (s);
}

char			*ft_itoa(int n)
{
	int		len;
	char	*s;
	long	k;
	int		i;

	k = n;
	len = ft_numlen(n);
	s = 0;
	i = 0;
	if (!(s = ft_itoa_new(s, k, len, i)))
		return (0);
	return (s);
}
