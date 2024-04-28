/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:27:31 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/24 17:32:53 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (haystack == NULL)
	{
		if (needle[0] == '\0')
			return ((char *)haystack);
		else
			return (NULL);
	}
	while (haystack[i] != '\0' && len > i)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && haystack[i + j] == needle[j] && i
				+ j < len)
				j++;
			if (needle[j] != '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
