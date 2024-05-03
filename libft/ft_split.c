/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:58 by sykawai           #+#    #+#             */
/*   Updated: 2024/05/02 16:14:05 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	int	co;

	co = 0;
	while (*s)
	{
		if (*s != c && (*(s - 1) == c || *(s - 1) == '\0'))
			co++;
		s++;
	}
	return (co);
}

int	ft_strlen_new(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strndup(const char *s, int n)
{
	char	*d;
	int		i;

	i = 0;
	d = malloc(sizeof(char) * (n + 1));
	if (!d)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[n] = '\0';
	return (d);
}

void	ft_free(char **j, int i)
{
	while (i >= 0)
		free(j[i--]);
	free(j);
}

char	**ft_split(char const *s, char c)
{
	char			**j;
	unsigned int	i;
	unsigned int	k;
	int				l;

	k = ft_count(s, c);
	j = (char **)malloc(sizeof(char *) * (k + 1));
	if (!j)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			l = ft_strlen_new(s, c);
			j[i] = ft_strndup(s, l);
			if (!j[i])
			{
				ft_free(j, i);
				return (NULL);
			}
			i++;
			s += l;
		}
	}
	j[i] = NULL;
	return (j);
}
