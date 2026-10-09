/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:47:54 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/12 12:47:54 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <signal.h>

static void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_heredoc_child(int fd[2], const char *finish_str,
		t_shell *shell)
{
	int	tty_fd;

	close(fd[0]);
	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd >= 0)
	{
		dup2(tty_fd, STDIN_FILENO);
		close(tty_fd);
	}
	setup_heredoc_signals();
	rl_clear_history();
	if (process_heredoc_loop(fd, finish_str, shell) == -1)
	{
		close(fd[1]);
		if (g_signal_received == SIGINT)
			exit(130);
		exit(1);
	}
	close(fd[1]);
	exit(0);
}

static int	handle_heredoc_parent(int fd[2], pid_t pid, t_shell *shell)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)
		|| (WIFEXITED(status) && WEXITSTATUS(status) != 0))
	{
		close(fd[0]);
		if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
		{
			shell->exit_status = 130;
			ft_putstr_fd("\n", STDERR_FILENO);
		}
		return (-1);
	}
	return (fd[0]);
}

static int	interactive_heredoc(int fd[2], const char *finish_str,
		t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		print_perror("fork");
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		handle_heredoc_child(fd, finish_str, shell);
	return (handle_heredoc_parent(fd, pid, shell));
}

int	read_heredoc_to_pipe(const char *finish_str, t_shell *shell)
{
	int	fd[2];

	if (pipe(fd) < 0)
	{
		print_perror("pipe");
		shell->exit_status = ERROR_PIPE;
		return (-1);
	}
	if (isatty(STDIN_FILENO))
		return (interactive_heredoc(fd, finish_str, shell));
	else
	{
		if (process_heredoc_loop(fd, finish_str, shell) == -1)
			return (-1);
		close(fd[1]);
		return (fd[0]);
	}
}
