/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:56:41 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/05 07:56:41 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

#define INITIAL_BUFFER_SIZE 1024

char	*init_or_expand_buffer(t_gnl_data *data)
{
	char	*new_buffer;
	int		new_size;

	if (!data->buffer)
	{
		data->buffer_size = INITIAL_BUFFER_SIZE;
		data->buffer = malloc(data->buffer_size);
		if (data->buffer)
			data->buffer[0] = '\0';
		return (data->buffer);
	}
	new_size = data->buffer_size * 2;
	new_buffer = malloc(new_size);
	if (!new_buffer)
		return (NULL);
	ft_memcpy(new_buffer, data->buffer, data->buffer_size);
	free(data->buffer);
	data->buffer = new_buffer;
	data->buffer_size = new_size;
	return (data->buffer);
}

static int	handle_leftover_data(t_gnl_data *data, int *total_read)
{
	if (data->leftover)
	{
		ft_strlcpy(data->buffer, data->leftover, data->buffer_size);
		*total_read = ft_strlen(data->leftover);
		free(data->leftover);
		data->leftover = NULL;
		return (1);
	}
	return (0);
}

static int	read_more_data(t_gnl_data *data, int *total_read)
{
	int	bytes_read;

	if (*total_read >= data->buffer_size - 1)
	{
		if (!init_or_expand_buffer(data))
			return (-1);
	}
	bytes_read = read(0, data->buffer + *total_read,
			data->buffer_size - *total_read - 1);
	if (bytes_read <= 0)
		return (0);
	*total_read += bytes_read;
	data->buffer[*total_read] = '\0';
	return (1);
}

char	*read_until_newline(t_gnl_data *data)
{
	int		total_read;
	char	*newline_pos;
	int		read_result;

	total_read = 0;
	handle_leftover_data(data, &total_read);
	while (1)
	{
		newline_pos = ft_strchr(data->buffer, '\n');
		if (newline_pos)
			break ;
		read_result = read_more_data(data, &total_read);
		if (read_result <= 0)
			break ;
	}
	if (total_read == 0)
		return (NULL);
	return (data->buffer);
}

char	*extract_line_and_save_leftover(t_gnl_data *data)
{
	char	*newline_pos;
	char	*line;
	int		line_len;

	newline_pos = ft_strchr(data->buffer, '\n');
	if (newline_pos)
	{
		line_len = newline_pos - data->buffer;
		line = ft_substr(data->buffer, 0, line_len);
		if (*(newline_pos + 1) != '\0')
			data->leftover = ft_strdup(newline_pos + 1);
	}
	else
	{
		line = ft_strdup(data->buffer);
	}
	return (line);
}
