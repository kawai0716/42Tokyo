/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:08 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/27 18:02:08 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "parser.h"

int		validate_syntax(t_token *tokens);
void	free_tokens(t_token *tokens);
void	process_line_with_semicolons(char *line, t_shell *shell);

void	handle_parse_error(t_shell *shell)
{
	print_error(NULL, "parse error");
	shell->exit_status = ERROR_SYNTAX;
}

void	handle_lexer_error(t_shell *shell)
{
	print_error(NULL, "lexer error");
	shell->exit_status = ERROR_SYNTAX;
}

void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;

	tokens = lexer(line, shell);
	if (tokens)
	{
		if (!validate_syntax(tokens))
		{
			shell->exit_status = ERROR_SYNTAX;
			free_tokens(tokens);
			return ;
		}
		free_tokens(tokens);
	}
	else if (shell->exit_status == 2)
	{
		return ;
	}
	process_line_with_semicolons(line, shell);
}
