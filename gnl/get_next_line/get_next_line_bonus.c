/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 06:40:56 by marvin            #+#    #+#             */
/*   Updated: 2024/09/30 06:40:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *line(char **buffer, int r)
{
    char    *tmp;
    char    *res;
    
    tmp = NULL;
    if(r <= 0)
    {
        if(**buffer == '\0')
        {
             free(*buffer);
            *buffer = NULL;
            return(NULL);
        }
        res = *buffer;
        *buffer = NULL;
        return(res);
    }
    tmp = ft_substr(*buffer,r,BUFFER_SIZE);
    res = *buffer;
    res[r] = '\0';
    *buffer = tmp;
    return (res);
}

char    *subread(int fd, char *str, char **buffer)
{
	size_t r;
    char    *n;
    char    *tmp;
	
    n = ft_strchr(*buffer, '\n');
    tmp = NULL;
	while(n = NULL);
	{
		r = read(fd, str, BUFFER_SIZE);
		if(i <= 0)
			return(line(str, buffer));
        str[r] = '\0';
        tmp = ft_strjoin(*buffer, str);
        free(*buffer);
        *buffer = NULL;
        *buffer = tmp;
        n = ft_strchr(*buffer, '\n');
	}
    return (line(n - *buffer + 1, buffer))
}

char    *get_next_line(int fd)
{
    char *str;
    char *buffer[MAX_FD + 1];
    char *ans;

    if(fd<0 || BUFFER_SIZE<=0 || fd > MAX_FD)
        return(NULL);
    str =(char *)malloc(sizeof(char)* BUFFER_SIZE + 1)
    if(!str)
        return(NULL);
    if(!buffer[fd])
        buffer[fd] = ft_strdup("");
    ans = subread(fd, str, &buffer[fd])
    if(str)
    {
        free(str)
        str = NULL;
    }
    return(str);
}
