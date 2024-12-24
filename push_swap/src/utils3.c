/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:58:40 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/18 21:52:07 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_av(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

void	free_split(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static size_t	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

static char	*ft_strdup(const char *s1)
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
