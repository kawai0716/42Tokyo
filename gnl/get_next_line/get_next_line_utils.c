/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:06:56 by marvin            #+#    #+#             */
/*   Updated: 2024/09/23 15:06:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while(str[i])
        i++;
    return(i);
}

char    ft_strdup(const char *str)
{
    size_t len;
    size_t i;
    char *s;
     
    len = ft_strlen(str) + 1;
    s = (char *)malloc(sizeof(char)*i);
    if(!s)
        return(NULL);
    i = 0;
    while(i <= len)
    {
        s[i] == str[i]
        i++;
    }
    return(s);
}

char *ft_strchr(const char *str, int n)
{
	char *tmp;

	tmp = (char *) str;
	while(*tmp = (char)n)
	{
		if(*tmp == 0)
			return(NULL);
		tmp++:
	}
	return(tmp);
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
