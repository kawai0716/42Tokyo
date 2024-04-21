/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:24:44 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/20 21:42:04 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(char *str)
{
	size_t	a;

	a = 0;
	while (*str != '\0')
	{
		a++;
		str++;
	}
	return (a);
}

char	*ft_strdup(const char *s1)
{
	size_t	n;
	char	*i;

	i = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	n = 0;
	if (i == NULL)
		return (0);
	while (ft_strlen(s1) > 0)
	{
		i = s1[n];
		n++;
	}
	return (i);
}
