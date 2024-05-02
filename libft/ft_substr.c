/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:24:19 by syuto             #+#    #+#             */
/*   Updated: 2024/04/24 19:18:58 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*i;
	size_t	j;
	size_t	k;

	i = (char *)malloc(sizeof(char) * (len + 1));
	j = 0;
	k = 0;
	if (i == 0)
		return (NULL);
	while (s[j] != '\0' && j <= start)
		j++;
	while (s[j] != '\0' && ft_strlen(s) > j + len)
	{
		i[k] = s[j];
		k++;
		j++;
	}
	i[k] = '\0';
	return (i);
}
