/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:39:24 by sykawai           #+#    #+#             */
/*   Updated: 2024/05/02 20:25:10 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;

	if (dst == NULL)
		return (ft_strlen(src) + size);
	a = ft_strlen(dst);
	b = ft_strlen(src);
	if (a >= size)
		return (b + size);
	else if (a < size)
	{
		while (*dst != '\0' && size > 1)
		{
			dst++;
			size--;
		}
		while (*src != '\0' && size > 1)
		{
			*dst++ = *src++;
			size--;
		}
		*dst = '\0';
		return (a + b);
	}
	return (0);
}
