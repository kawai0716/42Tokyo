/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:27:31 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/18 16:43:46 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char *ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t t;
	i=0;
	t=0;
	while(haystack[i]!='\0')
	{
		if(haystack[i]==needle[t])
		{
			i++;
			t++;
		}
		i++;
	}
}
