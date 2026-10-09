/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sykawai <sykawai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:09:43 by syuto             #+#    #+#             */
/*   Updated: 2024/06/14 21:11:41 by sykawai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../Libft/libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_printf_di(int i, int *n);
int		ft_printf_p(void *c, int *n);
int		ft_printf_u(unsigned int i, int *n);
int		ft_printf_x(unsigned int i, int *n);
int		ft_printf_x2(unsigned int i, int *n);
int		ft_printf_x3(unsigned long int i, int *n);
int		ft_putchar2(char c);
int		ft_putstr(char *str, int *n);

#endif
