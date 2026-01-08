/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:15:07 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/21 21:15:07 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define SUCCESS 0
# define ERROR_GENERAL 1
# define ERROR_SYNTAX 2
# define ERROR_MALLOC 12
# define ERROR_PIPE 13
# define ERROR_FORK 14
# define ERROR_EXEC 126
# define ERROR_COMMAND_NOT_FOUND 127
# define ERROR_SIGNAL_INT 130
# define ERROR_SIGNAL_QUIT 131

# define MINISHELL_PREFIX "minishell: "

void	print_error(const char *context, const char *message);
void	print_error_with_arg(const char *context, const char *arg,
			const char *message);
void	print_perror(const char *context);
void	*safe_malloc(size_t size, const char *context);
char	*safe_strdup(const char *s, const char *context);
void	handle_malloc_error(const char *context);
int		handle_syscall_error(const char *context, int return_value);

#endif