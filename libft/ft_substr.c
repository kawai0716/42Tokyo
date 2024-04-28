/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:24:19 by syuto             #+#    #+#             */
/*   Updated: 2024/04/23 11:17:23 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_substr(char const *s, unsigned int start,size_t len)
{
    char *i;
    size_t j;
    size_t k;
    i=(char *)malloc(sizeof(char)*(ft_strlen(s)+1));
    j=0;
    k=0;
    if(i==0)
        return(NULL);
    while(s[j]!='\0'&&j<=start)
        j++;
    while(s[j]!='\0'&&j<j+len)
    {
        i[k]=s[j];
        k++;
        j++;
    }
    i[k]='\0';
    return(i);
}
