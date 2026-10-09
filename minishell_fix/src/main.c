/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:08 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/27 18:02:08 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		print_error(NULL, "no arguments required");
		exit(ERROR_GENERAL);
	}
	minishell_loop(envp);
	return (EXIT_SUCCESS);
}
