#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

t_token	*new_token(t_token_type type, char *val)
{
	t_token	*tok = malloc(sizeof(t_token));
	tok->type = type;
	tok->value = strdup(val);
	tok->next = NULL;
	return (tok);
}

void	append_token(t_token **head, t_token *new_tok)
{
	if (!*head)
		*head = new_tok;
	else
	{
		t_token *cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new_tok;
	}
}

void	free_tokens(t_token *tok)
{
	t_token *next;
	while (tok)
	{
		next = tok->next;
		free(tok->value);
		free(tok);
		tok = next;
	}
}

void	print_indent(int depth)
{
	while (depth--)
		printf("  ");
}

void	print_ast(t_node *node, int depth)
{
	int	i;

	if (!node)
		return ;
	print_indent(depth);
	if (node->type == NODE_CMD)
	{
		printf("CMD:");
		for (i = 0; node->u_data.cmd.argv[i]; i++)
			printf(" [%s]", node->u_data.cmd.argv[i]);
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE:\n");
		print_ast(node->u_data.pipe.left, depth + 1);
		print_ast(node->u_data.pipe.right, depth + 1);
	}
	else if (node->type == NODE_REDIR)
	{
		printf("REDIR (%d) -> %s\n",
			node->u_data.redir.redir_type,
			node->u_data.redir.filename);
		print_ast(node->u_data.redir.child, depth + 1);
	}
}

void	run_test(const char *name, t_token *tokens)
{
	printf("=== TEST: %s ===\n", name);
	t_node *ast = parse(tokens);
	print_ast(ast, 0);
	free_tokens(tokens);
	printf("\n");
}

void	test_echo_hello_pipe_grep(void)
{
	t_token *toks = NULL;
	append_token(&toks, new_token(WORD, "echo"));
	append_token(&toks, new_token(WORD, "hello"));
	append_token(&toks, new_token(PIPE, "|"));
	append_token(&toks, new_token(WORD, "grep"));
	append_token(&toks, new_token(WORD, "h"));
	run_test("echo hello | grep h", toks);
}

void	test_ls_out_redirect(void)
{
	t_token *toks = NULL;
	append_token(&toks, new_token(WORD, "ls"));
	append_token(&toks, new_token(WORD, "-l"));
	append_token(&toks, new_token(REDIR_OUT, ">"));
	append_token(&toks, new_token(WORD, "out.txt"));
	run_test("ls -l > out.txt", toks);
}

void	test_cat_in_pipe_grep_append(void)
{
	t_token *toks = NULL;
	append_token(&toks, new_token(WORD, "cat"));
	append_token(&toks, new_token(REDIR_IN, "<"));
	append_token(&toks, new_token(WORD, "in.txt"));
	append_token(&toks, new_token(PIPE, "|"));
	append_token(&toks, new_token(WORD, "grep"));
	append_token(&toks, new_token(WORD, "test"));
	append_token(&toks, new_token(REDIR_APPEND, ">>"));
	append_token(&toks, new_token(WORD, "out.txt"));
	run_test("cat < in.txt | grep test >> out.txt", toks);
}

void	test_simple_cmd(void)
{
	t_token *toks = NULL;
	append_token(&toks, new_token(WORD, "pwd"));
	run_test("pwd", toks);
}

void	test_heredoc(void)
{
	t_token *toks = NULL;
	append_token(&toks, new_token(WORD, "cat"));
	append_token(&toks, new_token(HEREDOC, "<<"));
	append_token(&toks, new_token(WORD, "EOF"));
	run_test("cat << EOF", toks);
}

int	main(void)
{
	test_simple_cmd();
	test_echo_hello_pipe_grep();
	test_ls_out_redirect();
	test_cat_in_pipe_grep_append();
	test_heredoc();
	return (0);
}
