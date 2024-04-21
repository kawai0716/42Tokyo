/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:06:29 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/21 17:12:13 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) & (!s1[i] && !s2[i]))
	{
		if (s1[i] != s2[i])
		{
			if (s1[i] - s2[i] > 0)
				return (1);
			else if (s1[i] - s2[i] < 0)
				return (-1);
		}
	}
	return (0);
}
