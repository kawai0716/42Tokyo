#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
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

static void print_tokens(t_token *tokens) {
	for (t_token *cur = tokens; cur; cur = cur->next)
		printf("[%s] \"%s\"\n", token_type_str(cur->type), cur->value);
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
	char *line;
	t_token *tokens;

	while ((line = readline("minishell$ ")) != NULL) {
		if (*line)
			add_history(line);
		tokens = lexer(line);
		print_tokens(tokens);
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return 0;
}
