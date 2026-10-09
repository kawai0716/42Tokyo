/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <assert.h>
#include <sys/wait.h>

void	test_echo_command(void)
{
	printf("=== Testing echo command ===\n");
	
	char *argv1[] = {"echo", "hello", "world", NULL};
	char *argv2[] = {"echo", "-n", "no", "newline", NULL};
	char *argv3[] = {"echo", "-nnn", "multiple", "n", NULL};
	char *argv4[] = {"echo", NULL};
	
	printf("Test 1: basic echo\n");
	assert(builtin_echo(argv1) == 0);
	
	printf("Test 2: echo with -n flag\n");
	assert(builtin_echo(argv2) == 0);
	
	printf("Test 3: echo with multiple n flags\n");
	assert(builtin_echo(argv3) == 0);
	
	printf("Test 4: echo with no arguments\n");
	assert(builtin_echo(argv4) == 0);
	
	printf("echo tests passed!\n\n");
}

void	test_pwd_command(void)
{
	printf("=== Testing pwd command ===\n");
	
	printf("Test 1: basic pwd\n");
	assert(builtin_pwd() == 0);
	
	printf("pwd tests passed!\n\n");
}

void	test_cd_command(void)
{
	printf("=== Testing cd command ===\n");
	
	t_env *env_list = NULL;
	set_env_value(&env_list, "HOME", "/tmp");
	set_env_value(&env_list, "PWD", "/Users/yuh/workspace/42/42cursus/minishell");
	set_env_value(&env_list, "OLDPWD", "/Users/yuh/workspace/42/42cursus");
	
	char *argv1[] = {"cd", "/tmp", NULL};
	char *argv2[] = {"cd", NULL};
	char *argv3[] = {"cd", "-", NULL};
	
	printf("Test 1: cd to specific directory\n");
	assert(builtin_cd(argv1, &env_list) == 0);
	
	printf("Test 2: cd to HOME\n");
	assert(builtin_cd(argv2, &env_list) == 0);
	
	printf("Test 3: cd to previous directory\n");
	assert(builtin_cd(argv3, &env_list) == 0);
	
	free_env_list(env_list);
	printf("cd tests passed!\n\n");
}

void	test_is_builtin(void)
{
	printf("=== Testing is_builtin function ===\n");
	
	assert(is_builtin("echo") == 1);
	assert(is_builtin("cd") == 1);
	assert(is_builtin("pwd") == 1);
	assert(is_builtin("export") == 1);
	assert(is_builtin("unset") == 1);
	assert(is_builtin("env") == 1);
	assert(is_builtin("exit") == 1);
	assert(is_builtin("ls") == 0);
	assert(is_builtin("cat") == 0);
	assert(is_builtin(NULL) == 0);
	
	printf("is_builtin tests passed!\n\n");
}

int	main(void)
{
	printf("Starting builtin command tests...\n\n");
	
	test_is_builtin();
	test_echo_command();
	test_pwd_command();
	test_cd_command();
	
	printf("All builtin tests passed!\n");
	return (0);
}
