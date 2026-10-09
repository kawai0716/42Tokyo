/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:56:02 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 02:56:02 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static int	normalize_exit_code(int code)
{
	if (code < 0)
		return (256 + (code % 256));
	return (code % 256);
}

static int	handle_exit_args(char **argv, t_shell *shell)
{
	long	exit_code;
	int		overflow;

	if (!is_numeric(argv[1]))
	{
		print_numeric_error(argv[1]);
		shell->exit_status = 2;
		return (0);
	}
	exit_code = custom_atol(argv[1], &overflow);
	if (overflow)
	{
		print_numeric_error(argv[1]);
		shell->exit_status = 2;
		return (0);
	}
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		shell->should_exit = 0;
		return (1);
	}
	shell->exit_status = normalize_exit_code((int)exit_code);
	return (0);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	if (isatty(0))
		ft_putstr_fd("exit\n", 1);
	shell->should_exit = 1;
	if (!argv[1])
		return (0);
	return (handle_exit_args(argv, shell));
}
