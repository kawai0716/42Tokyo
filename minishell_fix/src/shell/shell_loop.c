/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:30:42 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/05 15:30:42 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

char	*get_next_line_minishell(t_gnl_data *data);
void	free_gnl_data(t_gnl_data *data);

static void	interactive_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		if (g_signal_received)
			handle_signal(shell);
		line = readline("minishell$ ");
		if (g_signal_received)
			handle_signal(shell);
		if (!line)
		{
			if (isatty(0))
				ft_putstr_fd("exit\n", 1);
			shell->should_exit = 1;
			break ;
		}
		if (*line)
		{
			add_history(line);
			process_line(line, shell);
		}
		free(line);
		if (shell->should_exit)
			break ;
	}
}

static t_input_buffer	*preload_all_input(t_gnl_data *gnl_data)
{
	t_input_buffer	*buffer;
	char			*line;

	buffer = malloc(sizeof(t_input_buffer));
	if (!buffer)
		return (NULL);
	buffer->lines = malloc(sizeof(char *) * 10000);
	if (!buffer->lines)
	{
		free(buffer);
		return (NULL);
	}
	buffer->current = 0;
	buffer->total = 0;
	while (buffer->total < 9999)
	{
		line = get_next_line_minishell(gnl_data);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		buffer->lines[buffer->total++] = line;
	}
	buffer->lines[buffer->total] = NULL;
	return (buffer);
}

static void	process_buffered_input(t_shell *shell, t_input_buffer *buffer)
{
	char	*line;

	while (buffer->current < buffer->total && !shell->should_exit)
	{
		if (g_signal_received)
			handle_signal(shell);
		line = ft_strdup(buffer->lines[buffer->current++]);
		if (!line)
			break ;
		shell->current_line = line;
		shell->heredoc_buffer_index = buffer->current;
		process_line(line, shell);
		if (shell->heredoc_buffer_index > buffer->current)
			buffer->current = shell->heredoc_buffer_index;
		free(line);
		shell->current_line = NULL;
	}
}

static void	non_interactive_loop(t_shell *shell)
{
	t_gnl_data		gnl_data;
	t_input_buffer	*buffer;
	int				i;

	ft_memset(&gnl_data, 0, sizeof(gnl_data));
	shell->gnl_data = &gnl_data;
	buffer = preload_all_input(&gnl_data);
	if (!buffer)
	{
		free_gnl_data(&gnl_data);
		return ;
	}
	shell->input_buffer = buffer;
	shell->heredoc_buffer_index = 0;
	process_buffered_input(shell, buffer);
	i = 0;
	while (buffer->lines && i < buffer->total)
		free(buffer->lines[i++]);
	if (buffer->lines)
		free(buffer->lines);
	free(buffer);
	free_gnl_data(&gnl_data);
	shell->gnl_data = NULL;
	shell->input_buffer = NULL;
}

void	minishell_loop(char **envp)
{
	t_shell	*shell;
	int		exit_status;

	init_signal();
	shell = init_shell(envp);
	if (!shell)
		exit(ERROR_GENERAL);
	if (isatty(0))
		interactive_loop(shell);
	else
		non_interactive_loop(shell);
	exit_status = shell->exit_status;
	cleanup_shell(shell);
	exit(exit_status);
}
