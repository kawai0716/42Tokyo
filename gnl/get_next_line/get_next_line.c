/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:25:42 by marvin            #+#    #+#             */
/*   Updated: 2024/09/22 19:25:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *subread(int fd, char *str, char **buffer)
{
	size_t i;
	
	while(ft_strchr(*buffer, '\n' == NULL)
	{
		i = read(fd, str, BUFFER_SIZE);
		if(i < 0)
			return(
	}
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
