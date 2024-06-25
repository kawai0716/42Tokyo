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

char *get_next_line(int fd)
{
    char *save;
    char *str;
    size_t subread;
    str = (char *)malloc(BUFFER_SIZE + 1);
    save = NULL;
    if(!str || fd != 0)
        return (NULL);
    while(strchr(save, '\n') == NULL)
    {
        subread = read (fd, str, BUFFER_SIZE);
        if(subread = 0)
            break;
        save = strjoin(save, str);
    }
}