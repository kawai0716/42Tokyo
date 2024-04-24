/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:08:59 by sykawai           #+#    #+#             */
/*   Updated: 2024/04/22 17:30:51 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char *i;
    unsigned int j;
    unsigned int n;
    j=ft_strlen(s);
	i=(char *)malloc(sizeof(char) * (j+1));
    if(i==0)
        return(NULL);
    while(s[n]!='\0')
    {
        i=f(n,s[n]);
        i++;
    }
    i='\0';
    return(i);
}
