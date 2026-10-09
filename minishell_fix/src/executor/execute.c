/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/08/03 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"

void	execute_redir_external(t_node *cmd, t_redir_exec *re);
void	execute_redir_builtin(t_node *cmd, t_shell *shell);
t_node	*collect_redirections(t_node *cmd, t_node **redirs, int *count);
int		execute_redirections(t_node **redirs, int count, t_shell *shell);
int		has_control_chars(const char *str);
int		handle_assignment_result(int result, char ***new_argv, t_shell *shell);
int		handle_cmd_not_found(char *cmd_name, t_shell *shell);
int		check_path_errors(char *cmd_path, char *cmd_name, t_shell *shell);

static int	check_cmd_errors(char **argv, t_shell *shell)
{
	char	*cmd_path;
	int		ret;

	if (has_control_chars(argv[0]))
		return (handle_cmd_not_found(argv[0], shell));
	if (is_builtin(argv[0]))
	{
		ret = execute_builtin(argv, shell);
		if (!shell->should_exit)
			shell->exit_status = ret;
		return (0);
	}
	cmd_path = find_cmd_path(argv[0], shell);
	if (!cmd_path)
		return (handle_cmd_not_found(argv[0], shell));
	if (!check_path_errors(cmd_path, argv[0], shell))
	{
		free(cmd_path);
		return (0);
	}
	free(cmd_path);
	return (1);
}

static void	execute_external_cmd(t_node *cmd, char **new_argv, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		print_perror("fork");
		shell->exit_status = ERROR_FORK;
		free(new_argv);
		return ;
	}
	if (pid == 0)
	{
		set_child_signal_default();
		cmd->u_data.cmd.argv = new_argv;
		exec_cmd(cmd, shell);
	}
	free(new_argv);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	run_simple_cmd(t_node *cmd, t_shell *shell)
{
	char	**new_argv;
	int		result;

	if (!cmd || !cmd->u_data.cmd.argv || !cmd->u_data.cmd.argv[0]
		|| !cmd->u_data.cmd.argv[0][0])
		return ;
	result = process_assignments(cmd->u_data.cmd.argv, &new_argv, shell);
	if (!handle_assignment_result(result, &new_argv, shell))
		return ;
	if (!check_cmd_errors(new_argv, shell))
	{
		free(new_argv);
		return ;
	}
	execute_external_cmd(cmd, new_argv, shell);
}

void	execute_node(t_node *cmd, t_shell *shell)
{
	if (cmd->type == NODE_CMD)
		run_simple_cmd(cmd, shell);
	else if (cmd->type == NODE_REDIR)
		execute_redir_builtin(cmd, shell);
	else if (cmd->type == NODE_PIPE)
		ex_main(cmd, shell);
	else if (cmd->type == NODE_SEMICOLON)
	{
		execute_node(cmd->u_data.semicolon.left, shell);
		execute_node(cmd->u_data.semicolon.right, shell);
	}
}
