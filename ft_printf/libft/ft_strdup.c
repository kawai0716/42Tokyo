/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:24:44 by sykawai           #+#    #+#             */
/*   Updated: 2024/05/03 14:22:57 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	n;
	char	*i;

	i = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	n = 0;
	if (i == NULL)
		return (0);
	while (ft_strlen(s1) > n)
	{
		i[n] = s1[n];
		n++;
	}
	i[n] = '\0';
	return (i);
}
