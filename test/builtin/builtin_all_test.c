/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_all_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <assert.h>

void	test_export_command(void)
{
	printf("=== Testing export command ===\n");
	
	t_env *env_list = NULL;
	
	char *argv1[] = {"export", "TEST_VAR=test_value", NULL};
	char *argv2[] = {"export", "NEW_VAR", NULL};
	char *argv3[] = {"export", "INVALID-VAR=value", NULL};
	char *argv4[] = {"export", NULL};
	
	printf("Test 1: export with value\n");
	assert(builtin_export(argv1, &env_list) == 0);
	assert(ft_strncmp(get_env_value(env_list, "TEST_VAR"), "test_value", 11) == 0);
	
	printf("Test 2: export without value\n");
	assert(builtin_export(argv2, &env_list) == 0);
	assert(find_env_node(env_list, "NEW_VAR") != NULL);
	
	printf("Test 3: export with invalid identifier\n");
	assert(builtin_export(argv3, &env_list) == 1);
	
	printf("Test 4: export without arguments (print all)\n");
	assert(builtin_export(argv4, &env_list) == 0);
	
	free_env_list(env_list);
	printf("export tests passed!\n\n");
}

void	test_unset_command(void)
{
	printf("=== Testing unset command ===\n");
	
	t_env *env_list = NULL;
	set_env_value(&env_list, "TEST_VAR1", "value1");
	set_env_value(&env_list, "TEST_VAR2", "value2");
	
	char *argv1[] = {"unset", "TEST_VAR1", NULL};
	char *argv2[] = {"unset", "NONEXISTENT", NULL};
	char *argv3[] = {"unset", "INVALID-VAR", NULL};
	char *argv4[] = {"unset", NULL};
	
	printf("Test 1: unset existing variable\n");
	assert(builtin_unset(argv1, &env_list) == 0);
	assert(find_env_node(env_list, "TEST_VAR1") == NULL);
	assert(find_env_node(env_list, "TEST_VAR2") != NULL);
	
	printf("Test 2: unset non-existent variable\n");
	assert(builtin_unset(argv2, &env_list) == 0);
	
	printf("Test 3: unset with invalid identifier\n");
	assert(builtin_unset(argv3, &env_list) == 1);
	
	printf("Test 4: unset without arguments\n");
	assert(builtin_unset(argv4, &env_list) == 0);
	
	free_env_list(env_list);
	printf("unset tests passed!\n\n");
}

void	test_env_command(void)
{
	printf("=== Testing env command ===\n");
	
	t_env *env_list = NULL;
	set_env_value(&env_list, "PATH", "/usr/bin");
	set_env_value(&env_list, "HOME", "/home/user");
	set_env_value(&env_list, "EMPTY_VAR", "");
	
	printf("Test 1: basic env command\n");
	assert(builtin_env(env_list) == 0);
	
	free_env_list(env_list);
	printf("env tests passed!\n\n");
}

void	test_execute_builtin(void)
{
	printf("=== Testing execute_builtin ===\n");
	
	t_env *env_list = NULL;
	set_env_value(&env_list, "HOME", "/tmp");
	
	char *argv1[] = {"echo", "hello", NULL};
	char *argv2[] = {"pwd", NULL};
	char *argv3[] = {"env", NULL};
	char *argv4[] = {"invalid", NULL};
	char *argv5[] = {NULL};
	
	printf("Test 1: execute echo\n");
	assert(execute_builtin(argv1, &env_list) == 0);
	
	printf("Test 2: execute pwd\n");
	assert(execute_builtin(argv2, &env_list) == 0);
	
	printf("Test 3: execute env\n");
	assert(execute_builtin(argv3, &env_list) == 0);
	
	printf("Test 4: execute non-builtin\n");
	assert(execute_builtin(argv4, &env_list) == 1);
	
	printf("Test 5: execute with NULL argv\n");
	assert(execute_builtin(argv5, &env_list) == 1);
	
	free_env_list(env_list);
	printf("execute_builtin tests passed!\n\n");
}

void	test_integration_scenario(void)
{
	printf("=== Testing integration scenario ===\n");
	
	t_env *env_list = NULL;
	
	char *init_envp[] = {
		"PATH=/usr/bin:/bin",
		"HOME=/home/user",
		"USER=testuser",
		NULL
	};
	
	env_list = array_to_env_list(init_envp);
	
	char *export_argv[] = {"export", "MY_VAR=my_value", NULL};
	assert(builtin_export(export_argv, &env_list) == 0);
	
	//char *env_argv[] = {"env", NULL};
	printf("Environment after export:\n");
	assert(builtin_env(env_list) == 0);
	
	char *unset_argv[] = {"unset", "USER", NULL};
	assert(builtin_unset(unset_argv, &env_list) == 0);
	
	printf("\nEnvironment after unset:\n");
	assert(builtin_env(env_list) == 0);
	
	assert(get_env_value(env_list, "MY_VAR") != NULL);
	assert(get_env_value(env_list, "USER") == NULL);
	assert(get_env_value(env_list, "PATH") != NULL);
	
	free_env_list(env_list);
	printf("\nIntegration scenario tests passed!\n\n");
}

int	main(void)
{
	printf("Starting comprehensive builtin tests...\n\n");
	
	test_export_command();
	test_unset_command();
	test_env_command();
	test_execute_builtin();
	test_integration_scenario();
	
	printf("All comprehensive builtin tests passed!\n");
	return (0);
}
