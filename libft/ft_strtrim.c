/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:22:52 by syuto             #+#    #+#             */
/*   Updated: 2024/04/28 15:42:39 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*t;
	size_t	s;
	size_t	e;
	size_t	l;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	while (s1[s] && ft_strchr(set, s1[s]))
		s++;
	e = ft_strlen(s1);
	while (e > s && ft_strchr(set, s1[e - 1]))
		e--;
	l = e - s;
	t = malloc(sizeof(char) * (l + 1));
	if (!t)
		return (NULL);
	ft_strlcpy(t, s1 + s, l + 1);
	return (t);
}
