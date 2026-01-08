/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 12:39:43 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/21 12:39:43 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

void	*safe_malloc(size_t size, const char *context)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		print_error(context, "memory allocation failed");
		exit(ERROR_MALLOC);
	}
	return (ptr);
}

char	*safe_strdup(const char *s, const char *context)
{
	char	*dup;

	dup = ft_strdup(s);
	if (!dup)
	{
		print_error(context, "memory allocation failed");
		exit(ERROR_MALLOC);
	}
	return (dup);
}

void	handle_malloc_error(const char *context)
{
	print_error(context, "memory allocation failed");
	exit(ERROR_MALLOC);
}

int	handle_syscall_error(const char *context, int return_value)
{
	if (return_value == -1)
	{
		print_perror(context);
		return (ERROR_GENERAL);
	}
	return (SUCCESS);
}
