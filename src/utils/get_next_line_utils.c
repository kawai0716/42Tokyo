/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 07:56:41 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/05 07:56:41 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*read_until_newline(t_gnl_data *data);
char	*extract_line_and_save_leftover(t_gnl_data *data);
char	*init_or_expand_buffer(t_gnl_data *data);

char	*get_next_line_minishell(t_gnl_data *data)
{
	char	*buffer_content;
	char	*line;

	if (!data)
		return (NULL);
	if (!data->buffer && !init_or_expand_buffer(data))
		return (NULL);
	buffer_content = read_until_newline(data);
	if (!buffer_content)
		return (NULL);
	line = extract_line_and_save_leftover(data);
	return (line);
}

void	free_gnl_data(t_gnl_data *data)
{
	if (!data)
		return ;
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data->leftover)
	{
		free(data->leftover);
		data->leftover = NULL;
	}
	data->buffer_size = 0;
}
