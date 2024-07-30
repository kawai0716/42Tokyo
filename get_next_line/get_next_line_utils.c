/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:40:19 by syuto             #+#    #+#             */
/*   Updated: 2024/06/18 13:52:51 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "get_next_line.h"

size_t strlen(char *c)
{
    size_t i;
    i = 0;
    while(*c)
    {
        c++;
        i++;
    }
    return(i);
}

//文字探索
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

//文字連結
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

//　\n文字から後ろの文字列を抽出するため
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

// 終端に達した文字列をコピーして返す
char	*ft_strdup(const char *s1)
{
	size_t	n;
	char	*i;

	i = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	n = 0;
	if (i == NULL)
		return (NULL);
	while (ft_strlen(s1) > n)
	{
		i[n] = s1[n];
		n++;
	}
	i[n] = '\0';
	return (i);
}
