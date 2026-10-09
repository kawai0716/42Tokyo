/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:51:08 by sykawai           #+#    #+#             */
/*   Updated: 2024/12/18 19:51:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_count(char const *s, char c)
{
	int	co;

	co = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			co++;
		s++;
	}
	return (co);
}

static int	ft_strlen_new(char const *s, char c)
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

static void	ft_free(char **j, int i)
{
	while (i > 0)
		free(j[i--]);
	free(j);
}

static void	process(char const *s, char c, char **j, unsigned int *i)
{
	while (*s)
	{
		if (*s != c)
		{
			j[*i] = ft_substr(s, 0, ft_strlen_new(s, c));
			if (!j[*i])
			{
				ft_free(j, *i - 1);
				return ;
			}
			s += ft_strlen_new(s, c);
			(*i)++;
		}
		else
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**j;
	unsigned int	i;

	if (!s)
		return (NULL);
	j = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!j)
		return (NULL);
	i = 0;
	process(s, c, j, &i);
	j[i] = NULL;
	return (j);
}
