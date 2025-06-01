#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

typedef struct {
	const char *value;
	t_token_type type;
} ExpectedToken;

typedef struct {
	const char *input;
	ExpectedToken expected[16];
	int expected_count;
} TestCase;

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

static void free_tokens(t_token *token) {
	t_token *next;
	while (token) {
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

static int run_test(const TestCase *test) {
	t_token *tokens = lexer(test->input);
	t_token *cur = tokens;
	int ok = 1;

	for (int i = 0; i < test->expected_count; ++i) {
		if (!cur) {
			ok = 0;
			break;
		}
		if (cur->type != test->expected[i].type ||
			strcmp(cur->value, test->expected[i].value) != 0) {
			ok = 0;
			break;
		}
		cur = cur->next;
	}
	if (cur != NULL) // トークンが余っていたらNG
		ok = 0;

	printf("%s: %s\n", ok ? "[OK] " : "[FAIL]", test->input);
	if (!ok) {
		printf("Expected:\n");
		for (int i = 0; i < test->expected_count; ++i)
			printf("  [%s] \"%s\"\n", token_type_str(test->expected[i].type), test->expected[i].value);
		printf("Got:\n");
		cur = tokens;
		while (cur) {
			printf("  [%s] \"%s\"\n", token_type_str(cur->type), cur->value);
			cur = cur->next;
		}
	}
	free_tokens(tokens);
	return ok;
}

int main(void) {
	TestCase tests[] = {
		{
			.input = "ls -la",
			.expected = {
				{"ls", WORD}, {"-la", WORD}
			}, .expected_count = 2
		},
		{
			.input = "echo \"hello world\"",
			.expected = {
				{"echo", WORD}, {"hello world", WORD}
			}, .expected_count = 2
		},
		{
			.input = "cat < infile.txt",
			.expected = {
				{"cat", WORD}, {"<", REDIR_IN}, {"infile.txt", WORD}
			}, .expected_count = 3
		},
		{
			.input = "echo \"a > b\" > file",
			.expected = {
				{"echo", WORD}, {"a > b", WORD}, {">", REDIR_OUT}, {"file", WORD}
			}, .expected_count = 4
		},
		{
			.input = "echo ''",
			.expected = {
				{"echo", WORD}, {"", WORD}
			}, .expected_count = 2
		},
		{
			.input = "echo 'a | b'",
			.expected = {
				{"echo", WORD}, {"a | b", WORD}
			}, .expected_count = 2
		},
		{
			.input = "echo hello>>log.txt",
			.expected = {
				{"echo", WORD}, {"hello", WORD}, {">>", REDIR_APPEND}, {"log.txt", WORD}
			}, .expected_count = 4
		},
	};
	int passed = 0;
	int total = sizeof(tests) / sizeof(tests[0]);

	for (int i = 0; i < total; ++i)
		passed += run_test(&tests[i]);

	printf("\nPassed %d/%d tests\n", passed, total);
	return (passed == total ? 0 : 1);
}
