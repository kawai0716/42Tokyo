/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:53:55 by syuto             #+#    #+#             */
/*   Updated: 2024/06/24 00:37:16 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "get_next_line.h"

char *result(char *save)
{
	size_t i;
	size_t j;
	char *nl;
	char *answer;
	char *c;
	if((nl = strchr(save, '\n')) != NULL)
	{
		i = strlen(save);
		j = nl - save +1;
		answer = ft_substr(save, 0, j);
		c = save;
		save = ft_substr(save, j, i-j);
		free (c);
		return (answer);
	}
	else if(save)
	{
		answer = strdup(save);
		free (save);
		save = NULL;
		return (answer);
	}
	return (0);
}

char *get_next_line(int fd)
{
    char *save;
    char *str;
    char *c;
    size_t subread;
    str = (char *)malloc(BUFFER_SIZE + 1);
    save = NULL;
    if(!str || fd < 0)
        return (NULL);
    while(strchr(save, '\n') == NULL)
    {
        subread = read (fd, str, BUFFER_SIZE);
        if(subread <= 0)
		{
			free (str);
			free (save);
			return (NULL);
		}
		str[subread] = '\0';
        c = save;
        save = strjoin(save, str);
        free (c);
	}
	free (str);
	return (result(save));
}
