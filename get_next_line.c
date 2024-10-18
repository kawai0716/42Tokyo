/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 11:27:43 by prafael-          #+#    #+#             */
/*   Updated: 2024/10/18 18:07:35 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*line(int bytes, char **buffer)
{
	char	*ans;
	char	*tmp;

	tmp = NULL;
	if (bytes <= 0)
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
	tmp = ft_substr(*buffer, bytes, BUFFER_SIZE);
	ans = *buffer;
	ans[bytes] = 0;
	*buffer = tmp;
	return (ans);
}

char	*subread(int fd, char **buffer, char *str)
{
	ssize_t	bytes;
	char	*tmp;
	char	*n;

	n = ft_strchr(*buffer, '\n');
	tmp = NULL;
	bytes = 0;
	while (n == NULL)
	{
		bytes = read(fd, str, BUFFER_SIZE);
		if (bytes <= 0)
			return (line(bytes, buffer));
		str[bytes] = 0;
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
