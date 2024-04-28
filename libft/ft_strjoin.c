/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:18:01 by syuto             #+#    #+#             */
/*   Updated: 2024/04/23 12:22:23 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    char *i;
    size_t j;
    size_t n;
    size_t k;
    i=(char *)malloc(sizeof(char)*(ft_strlen(s1)+ft_strlen(s2)+1));
    j=0;
    n=0;
    k=0;
    if(!i)
        return(NULL);
    while(s1[j]!='\0')
    {
        i[n]=s1[j];
        n++;
        j++;
    }
    while(s2[k]!='\0')
    {
        i[n]=s2[k];
        n++;
        k++;
    }
    i='\0';
    return(i);
}
