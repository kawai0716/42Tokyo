/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:40:09 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/24 15:33:12 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (d < s)
	{
		while (len-- != 0)
			*d++ = *s++;
	}
	else if (d > s)
	{
		d += len;
		s += len;
		while (len-- != 0)
			*--d = *--s;
	}
	return (dest);
}
