/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:35:44 by yuhashim          #+#    #+#             */
/*   Updated: 2025/07/19 16:35:44 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "error.h"

void	process_single_command(char *cmd, t_shell *shell);
void	handle_parse_error(t_shell *shell);
void	handle_lexer_error(t_shell *shell);

static int	find_unquoted_semicolon(char *line, int start)
{
	int		i;
	int		in_single;
	int		in_double;

	i = start;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double && (i == 0 || line[i - 1] != '\\'))
			in_single = !in_single;
		else if (line[i] == '"' && !in_single
			&& (i == 0 || line[i - 1] != '\\'))
			in_double = !in_double;
		else if (line[i] == ';' && !in_single && !in_double)
			return (i);
		i++;
	}
	return (-1);
}

static char	*extract_command(char *line, int start, int end)
{
	char	*cmd;
	int		len;

	if (end == -1)
		len = ft_strlen(line) - start;
	else
		len = end - start;
	while (start < start + len && line[start] == ' ')
	{
		start++;
		len--;
	}
	while (len > 0 && line[start + len - 1] == ' ')
		len--;
	if (len <= 0)
		return (NULL);
	cmd = ft_substr(line, start, len);
	return (cmd);
}

void	process_line_with_semicolons(char *line, t_shell *shell)
{
	int		start;
	int		end;
	char	*cmd;

	start = 0;
	while (1)
	{
		end = find_unquoted_semicolon(line, start);
		cmd = extract_command(line, start, end);
		if (cmd)
		{
			shell->current_cmd = cmd;
			process_single_command(cmd, shell);
			free(cmd);
			shell->current_cmd = NULL;
		}
		if (end == -1)
			break ;
		start = end + 1;
	}
}

void	process_single_command(char *cmd, t_shell *shell)
{
	t_token	*tokens;
	t_node	*ast;

	tokens = lexer(cmd, shell);
	if (tokens)
	{
		ast = parse(tokens, shell);
		if (ast)
		{
			shell->shell_mode = MODE_EXECUTING;
			shell->current_ast = ast;
			shell->current_tokens = tokens;
			set_execution_signal();
			execute_node(ast, shell);
			restore_interactive_signal();
			shell->shell_mode = MODE_INTERACTIVE;
			shell->current_ast = NULL;
			shell->current_tokens = NULL;
			free_ast(ast);
		}
		else if (shell->exit_status != 2)
			handle_parse_error(shell);
		free_tokens(tokens);
	}
}
