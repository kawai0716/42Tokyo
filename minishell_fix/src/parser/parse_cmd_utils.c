/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:44:30 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/01 10:44:30 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node			*parse_redirection(t_token **tokens, t_node *child);
size_t			count_words(t_token *tokens);
void			free_argv_partial(char **argv, size_t count);
int				process_token(t_token **tokens, char **argv, size_t *i);
int				is_redirection(t_token_type type);

static int	count_skip_and_alloc(char **argv, char ***new_argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] && argv[i][0] == '\0')
		i++;
	if (i == 0)
		return (0);
	j = 0;
	while (argv[i + j])
		j++;
	*new_argv = malloc(sizeof(char *) * (j + 1));
	if (!*new_argv)
		return (0);
	return (i);
}

static char	**skip_empty_strings(char **argv)
{
	char	**new_argv;
	int		skip_count;
	int		i;
	int		j;

	skip_count = count_skip_and_alloc(argv, &new_argv);
	if (skip_count == 0)
		return (argv);
	j = 0;
	while (j < skip_count)
	{
		free(argv[j]);
		j++;
	}
	i = skip_count;
	j = 0;
	while (argv[i])
		new_argv[j++] = argv[i++];
	new_argv[j] = NULL;
	free(argv);
	return (new_argv);
}

static char	**dup_argv_mixed(t_token **tokens)
{
	char	**argv;
	size_t	i;
	int		result;

	argv = malloc(sizeof(char *) * (count_words(*tokens) + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens)
	{
		result = process_token(tokens, argv, &i);
		if (result == 0)
		{
			free_argv_partial(argv, i);
			return (NULL);
		}
		else if (result == -1)
			break ;
	}
	argv[i] = NULL;
	return (skip_empty_strings(argv));
}

static t_node	*handle_redirections(t_token **tokens, t_node *cmd)
{
	while (*tokens)
	{
		if ((*tokens)->type == WORD)
			*tokens = (*tokens)->next;
		else if (is_redirection((*tokens)->type))
		{
			cmd = parse_redirection(tokens, cmd);
			if (!cmd)
				return (NULL);
		}
		else
			break ;
	}
	return (cmd);
}

t_node	*parse_command(t_token **tokens)
{
	t_node	*cmd;
	t_token	*backup;

	cmd = malloc(sizeof(t_node));
	if (!cmd)
		return (NULL);
	cmd->type = NODE_CMD;
	backup = *tokens;
	cmd->u_data.cmd.argv = dup_argv_mixed(tokens);
	if (!cmd->u_data.cmd.argv)
	{
		free(cmd);
		return (NULL);
	}
	*tokens = backup;
	return (handle_redirections(tokens, cmd));
}
