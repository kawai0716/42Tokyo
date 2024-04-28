/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:22:52 by syuto             #+#    #+#             */
/*   Updated: 2024/04/28 13:11:45 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtrim(char const *s1, char const *set)
{
    char *i;
    size_t j;
    size_t k;
    i=(char *)malloc(sizeof(char)*(ft_strlen(s1)+1));
    j=0;
    k=0;
    if(!i)
        return(NULL);
    while(s1[j]!=0)
    {
        if(s1[j]==set[0])
            i++;
        
    }
}
