/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 22:09:49 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/21 22:09:49 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"

static void	init_shell_fields(t_shell *shell)
{
	shell->shell_mode = MODE_INTERACTIVE;
	shell->exit_status = 0;
	shell->should_exit = 0;
	shell->gnl_data = NULL;
	shell->heredoc_gnl_data = NULL;
	shell->input_buffer = NULL;
	shell->heredoc_buffer_index = 0;
	shell->current_ast = NULL;
	shell->current_tokens = NULL;
	shell->current_line = NULL;
	shell->current_cmd = NULL;
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)safe_malloc(sizeof(t_shell), "init_shell");
	if (!shell)
		return (NULL);
	init_shell_fields(shell);
	shell->envp = dup_envp(envp);
	if (!shell->envp)
	{
		free(shell);
		return (NULL);
	}
	shell->env_list = init_env_list(shell->envp);
	if (!shell->env_list)
	{
		free_envp_array(shell->envp);
		free(shell);
		return (NULL);
	}
	return (shell);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

static void	free_cmd_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_ast(t_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_CMD)
	{
		if (ast->u_data.cmd.argv)
			free_cmd_argv(ast->u_data.cmd.argv);
	}
	else if (ast->type == NODE_PIPE)
	{
		free_ast(ast->u_data.pipe.left);
		free_ast(ast->u_data.pipe.right);
	}
	else if (ast->type == NODE_REDIR)
	{
		if (ast->u_data.redir.filename)
			free(ast->u_data.redir.filename);
		free_ast(ast->u_data.redir.child);
	}
	free(ast);
}
