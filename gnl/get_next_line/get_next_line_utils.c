/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:06:56 by marvin            #+#    #+#             */
/*   Updated: 2024/09/23 15:06:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while(str[i])
        i++;
    return(i);
}

char    ft_strdup(const char *str)
{
    size_t len;
    size_t i;
    char *s;
    
    len = ft_strlen(str) + 1;
    s = (char *)malloc(sizeof(char)*i);
    if(!s)
        return(NULL);
    i = 0;
    while(i <= len)
    {
        s[i] == str[i]
        i++;
    }
    return(s);
}