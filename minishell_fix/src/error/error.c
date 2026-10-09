/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 08:38:40 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/21 08:38:40 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"

void	print_error(const char *context, const char *message)
{
	ft_putstr_fd((char *)MINISHELL_PREFIX, STDERR_FILENO);
	if (context)
	{
		ft_putstr_fd((char *)context, STDERR_FILENO);
		ft_putstr_fd((char *)": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)message, STDERR_FILENO);
	ft_putstr_fd((char *)"\n", STDERR_FILENO);
}

void	print_error_with_arg(const char *context, const char *arg,
			const char *message)
{
	ft_putstr_fd((char *)MINISHELL_PREFIX, STDERR_FILENO);
	if (context)
	{
		ft_putstr_fd((char *)context, STDERR_FILENO);
		ft_putstr_fd((char *)": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd((char *)": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)message, STDERR_FILENO);
	ft_putstr_fd((char *)"\n", STDERR_FILENO);
}

void	print_perror(const char *context)
{
	ft_putstr_fd((char *)MINISHELL_PREFIX, STDERR_FILENO);
	if (context)
	{
		ft_putstr_fd((char *)context, STDERR_FILENO);
		ft_putstr_fd((char *)": ", STDERR_FILENO);
	}
	perror("");
}
