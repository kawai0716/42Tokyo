/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:18:01 by syuto             #+#    #+#             */
/*   Updated: 2024/05/04 14:54:43 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*i;
	size_t	j;
	size_t	n;
	size_t	k;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	i = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	j = 0;
	n = 0;
	k = 0;
	if (!i)
		return (NULL);
	while (s1[j] != '\0')
		i[n++] = s1[j++];
	while (s2[k] != '\0')
		i[n++] = s2[k++];
	i[n] = '\0';
	return (i);
}
