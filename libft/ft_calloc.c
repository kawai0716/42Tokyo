/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:44:23 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/24 17:25:23 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*i;

	i = (void *)malloc(count * size);
	if (i == NULL)
		return (NULL);
	ft_bzero(i, count * size);
	return (i);
}
