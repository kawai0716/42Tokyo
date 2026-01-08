/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:25:33 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/21 16:25:33 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"
#include "minishell.h"
#include <signal.h>

int	process_heredoc_line(char *line, t_heredoc *h, int *done)
{
	if (ft_strcmp(line, h->finish_str) == 0)
	{
		free(line);
		*done = 1;
		return (0);
	}
	if (write(h->fd[1], line, ft_strlen(line)) == -1
		|| write(h->fd[1], "\n", 1) == -1)
	{
		print_perror("write");
		free(line);
		close(h->fd[0]);
		close(h->fd[1]);
		h->shell->exit_status = ERROR_GENERAL;
		return (-1);
	}
	free(line);
	return (0);
}

static void	init_heredoc_context(t_heredoc *h, int fd[2],
		const char *finish_str, t_shell *shell)
{
	h->finish_str = finish_str;
	h->fd = fd;
	h->shell = shell;
}

static char	*get_heredoc_line(t_heredoc *h)
{
	char	*line;

	if (h->shell->input_buffer
		&& h->shell->heredoc_buffer_index < h->shell->input_buffer->total)
	{
		if (!h->shell->input_buffer->lines)
			return (NULL);
		if (!h->shell->input_buffer->lines[h->shell->heredoc_buffer_index])
			return (NULL);
		line = ft_strdup(h->shell->input_buffer->lines
			[h->shell->heredoc_buffer_index]);
		h->shell->heredoc_buffer_index++;
		return (line);
	}
	else
		return (get_next_line_minishell(h->shell->gnl_data));
}

static int	handle_heredoc_input(t_heredoc *h, int *done)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		line = readline("> ");
		if (!line)
			return (1);
	}
	else
	{
		line = get_heredoc_line(h);
		if (!line)
			return (1);
	}
	if (process_heredoc_line(line, h, done) == -1)
		return (-1);
	return (0);
}

int	process_heredoc_loop(int fd[2], const char *finish_str, t_shell *shell)
{
	int			done;
	t_heredoc	h;
	int			old_mode;
	int			ret;

	done = 0;
	init_heredoc_context(&h, fd, finish_str, shell);
	old_mode = shell->shell_mode;
	shell->shell_mode = MODE_HEREDOC;
	while (!done)
	{
		ret = handle_heredoc_input(&h, &done);
		if (ret == -1)
		{
			shell->shell_mode = old_mode;
			return (-1);
		}
		if (ret == 1)
			break ;
	}
	shell->shell_mode = old_mode;
	return (0);
}
