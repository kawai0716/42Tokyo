/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syuto <syuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:09:42 by syuto             #+#    #+#             */
/*   Updated: 2024/06/04 21:10:12 by syuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H


# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdarg.h>


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#ifndef MAX_FD
#define MAX_FD 1024
#endif


char *get_next_line(int fd);
size_t strlen(char *c);
size_t strlen2(char *c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);


#endif
