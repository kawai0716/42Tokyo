/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:30:47 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/20 17:30:54 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;
	i=0;
	char *one=s1;
	char *two=s2;
	while(i<n)
	{
		if(one[i]!=two[i])
		{
			if(one[i]-two[i]>0)
				return(1);
			if(one[i]-two[i]<0)
				return(-1);
		}
		i++;
	}
	return(0);
}
