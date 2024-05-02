/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:58 by sykawai           #+#    #+#             */
/*   Updated: 2024/05/02 13:05:36 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_split(char const *s, char c)
{
    char **i;
    unsigned int j;
    unsigned int k;
    j=ft_strlen(s);
    k=0;
    i=(char **)malloc(sizeof(char *)*(j+1));
    while(s[k])
    {
        if(s[k]==c);
            k++;
    }

}


// int ft_strlen_c(const char *s, char c)
// {
//     int len;

//     len = 0;
//     while (*s != c && *s != '\0')
//     {
//         len++;
//         s++;
//     }
//     return (len);
// }

// char *ft_strndup(const char *s, int n)
// {
//     char *dup;

//     dup = malloc(sizeof(char) * (n + 1));
//     if (!dup)
//         return (NULL);
//     dup[n] = '\0';
//     while (n--)
//         dup[n] = s[n];
//     return (dup);
// }

// char **ft_split(char const *s, char c)
// {
//     char **split;
//     int word_count;
//     int i;

//     // 部分文字列の数をカウント
//     word_count = /* ... */

//     split = malloc(sizeof(char *) * (word_count + 1));
//     if (!split)
//         return (NULL);

//     i = 0;
//     while (*s != '\0')
//     {
//         while (*s == c)
//             s++;
//         if (*s != '\0')
//         {
//             int len = ft_strlen_c(s, c);
//             split[i++] = ft_strndup(s, len);
//             if (!split[i]) 
//             {
//                 while (i >= 0)
//                     free(split[i--]);
//                 free(split);
//                 return (NULL);
//             }
//             i++;
//             s += len;
//         }
//     }
//     split[i] = NULL;
//     return (split);
// }