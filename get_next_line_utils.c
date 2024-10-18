/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:27:40 by prafael-          #+#    #+#             */
/*   Updated: 2024/10/18 16:43:44 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

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

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	j;
	size_t	i;

	j = 0;
	if (!s)
		return (NULL);
	while (s[j])
		j++;
	if (start >= j)
		return (ft_strdup(""));
	i = 0;
	while (s[start + i] && i < len)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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
