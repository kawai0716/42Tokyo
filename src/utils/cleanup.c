/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/27 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	free_gnl_data(t_gnl_data *data);
void	free_ast(t_node *ast);
void	free_tokens(t_token *tokens);

void	cleanup_shell(t_shell *shell)
{
	if (shell->envp)
		free_envp_array(shell->envp);
	if (shell->env_list)
		free_env_list(shell->env_list);
	rl_clear_history();
	free(shell);
}

static void	free_input_buffer(t_input_buffer *buffer)
{
	int	i;

	if (!buffer)
		return ;
	i = 0;
	while (buffer->lines && i < buffer->total)
		free(buffer->lines[i++]);
	if (buffer->lines)
		free(buffer->lines);
	free(buffer);
}

void	cleanup_shell_for_exec(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->current_ast)
		free_ast(shell->current_ast);
	if (shell->current_tokens)
		free_tokens(shell->current_tokens);
	if (shell->env_list)
		free_env_list(shell->env_list);
	if (shell->envp)
		free_split(shell->envp);
	if (shell->gnl_data)
		free_gnl_data(shell->gnl_data);
	if (shell->input_buffer)
		free_input_buffer(shell->input_buffer);
	if (shell->current_line)
		free(shell->current_line);
	if (shell->current_cmd)
		free(shell->current_cmd);
}
