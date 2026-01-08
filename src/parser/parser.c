/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 00:47:37 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 00:47:37 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "error.h"
#include "minishell.h"

t_node	*parse_pipeline(t_token **tokens);
t_node	*parse_semicolon(t_token **tokens);

static int	check_pipe_error(t_token *current)
{
	if (!current->next || current->next->type == PIPE)
	{
		print_error("syntax error near unexpected token", "`|'");
		return (0);
	}
	return (1);
}

static int	check_redir_error(t_token *current)
{
	if (!current->next || current->next->type != WORD)
	{
		if (!current->next)
			print_error("syntax error near unexpected token", "`newline'");
		else if (current->next->type == PIPE)
			print_error("syntax error near unexpected token", "`|'");
		else if (current->next->type == REDIR_IN)
			print_error("syntax error near unexpected token", "`<'");
		else if (current->next->type == REDIR_OUT)
			print_error("syntax error near unexpected token", "`>'");
		else if (current->next->type == REDIR_APPEND)
			print_error("syntax error near unexpected token", "`>>'");
		else if (current->next->type == HEREDOC)
			print_error("syntax error near unexpected token", "`<<'");
		else if (current->next->type == SEMICOLON)
			print_error("syntax error near unexpected token", "`;'");
		return (0);
	}
	return (1);
}

static int	validate_token_sequence(t_token *current)
{
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!check_pipe_error(current))
				return (0);
		}
		else if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_APPEND || current->type == HEREDOC)
		{
			if (!check_redir_error(current))
				return (0);
		}
		else if (current->type == SEMICOLON)
		{
			if (!current->next)
				return (1);
		}
		current = current->next;
	}
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (current->type == PIPE)
	{
		print_error("syntax error near unexpected token", "`|'");
		return (0);
	}
	if (current->type == SEMICOLON)
	{
		print_error("syntax error near unexpected token", "`;'");
		return (0);
	}
	return (validate_token_sequence(current));
}

t_node	*parse(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	if (!tokens || !validate_syntax(tokens))
	{
		shell->exit_status = ERROR_SYNTAX;
		return (NULL);
	}
	current = tokens;
	return (parse_semicolon(&current));
}
