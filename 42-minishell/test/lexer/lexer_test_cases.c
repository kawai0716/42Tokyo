#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

static const char *token_type_str(t_token_type type) {
	switch (type) {
		case WORD: return "WORD";
		case PIPE: return "PIPE";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_OUT: return "REDIR_OUT";
		case REDIR_APPEND: return "REDIR_APPEND";
		case HEREDOC: return "HEREDOC";
		default: return "UNKNOWN";
	}
}

static void print_tokens(const char *input, t_token *tokens) {
	printf("input: %s\n", input);
	for (t_token *cur = tokens; cur; cur = cur->next) {
		printf("  [%s] \"%s\"\n", token_type_str(cur->type), cur->value);
	}
	printf("\n");
}

static void free_tokens(t_token *tokens) {
	t_token *next;
	while (tokens) {
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

int main(void) {
	const char *tests[] = {
		"ls -la",
		"echo \"hello world\"",
		"cat < infile.txt",
		"grep \"pattern\" < in.txt > out.txt",
		"echo 'a | b'",
		"echo \"unclosed",
		"echo hello | wc -l",
		"echo hello>>log.txt",
		"echo \"a > b\" > file",
		"echo \"\""
	};
	const int test_count = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < test_count; ++i) {
		t_token *tokens = lexer(tests[i]);
		print_tokens(tests[i], tokens);
		free_tokens(tokens);
	}
	return 0;
}
