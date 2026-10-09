/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:26:48 by prafael-          #+#    #+#             */
/*   Updated: 2024/10/18 18:07:26 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*line(int byets, char **buffer)
{
	char	*ans;
	char	*tmp;

	tmp = NULL;
	if (byets <= 0)
	{
		if (**buffer == '\0')
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		ans = *buffer;
		*buffer = NULL;
		return (ans);
	}
	tmp = ft_substr(*buffer, byets, BUFFER_SIZE);
	ans = *buffer;
	ans[byets] = 0;
	*buffer = tmp;
	return (ans);
}

char	*subread(int fd, char **buffer, char *str)
{
	ssize_t	byets;
	char	*tmp;
	char	*n;

	n = ft_strchr(*buffer, '\n');
	tmp = NULL;
	byets = 0;
	while (n == NULL)
	{
		byets = read(fd, str, BUFFER_SIZE);
		if (byets <= 0)
			return (line(byets, buffer));
		str[byets] = 0;
		tmp = ft_strjoin(*buffer, str);
		free_null(buffer);
		*buffer = tmp;
		n = ft_strchr(*buffer, '\n');
	}
	return (line(n - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD + 1];
	char		*str;
	char		*ans;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	ans = subread(fd, &buffer[fd], str);
	free_null(&str);
	return (ans);
}
