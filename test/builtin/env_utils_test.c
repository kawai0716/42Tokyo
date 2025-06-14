/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:00:00 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/14 00:00:00 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <assert.h>

void	test_create_env_node(void)
{
	printf("=== Testing create_env_node ===\n");
	
	t_env *node = create_env_node("PATH", "/usr/bin");
	assert(node != NULL);
	assert(ft_strncmp(node->key, "PATH", 5) == 0);
	assert(ft_strncmp(node->value, "/usr/bin", 9) == 0);
	assert(node->next == NULL);
	
	free(node->key);
	free(node->value);
	free(node);
	
	printf("create_env_node tests passed!\n\n");
}

void	test_add_env_node(void)
{
	printf("=== Testing add_env_node ===\n");
	
	t_env *env_list = NULL;
	t_env *node1 = create_env_node("PATH", "/usr/bin");
	t_env *node2 = create_env_node("HOME", "/home/user");
	
	add_env_node(&env_list, node1);
	assert(env_list == node1);
	assert(env_list->next == NULL);
	
	add_env_node(&env_list, node2);
	assert(env_list == node1);
	assert(env_list->next == node2);
	assert(node2->next == NULL);
	
	free_env_list(env_list);
	printf("add_env_node tests passed!\n\n");
}

void	test_find_env_node(void)
{
	printf("=== Testing find_env_node ===\n");
	
	t_env *env_list = NULL;
	set_env_value(&env_list, "PATH", "/usr/bin");
	set_env_value(&env_list, "HOME", "/home/user");
	set_env_value(&env_list, "USER", "testuser");
	
	t_env *found = find_env_node(env_list, "PATH");
	assert(found != NULL);
	assert(ft_strncmp(found->key, "PATH", 5) == 0);
	
	found = find_env_node(env_list, "HOME");
	assert(found != NULL);
	assert(ft_strncmp(found->key, "HOME", 5) == 0);
	
	found = find_env_node(env_list, "NONEXISTENT");
	assert(found == NULL);
	
	free_env_list(env_list);
	printf("find_env_node tests passed!\n\n");
}

void	test_delete_env_node(void)
{
	printf("=== Testing delete_env_node ===\n");
	
	t_env *env_list = NULL;
	set_env_value(&env_list, "PATH", "/usr/bin");
	set_env_value(&env_list, "HOME", "/home/user");
	set_env_value(&env_list, "USER", "testuser");
	
	delete_env_node(&env_list, "HOME");
	t_env *found = find_env_node(env_list, "HOME");
	assert(found == NULL);
	
	found = find_env_node(env_list, "PATH");
	assert(found != NULL);
	
	found = find_env_node(env_list, "USER");
	assert(found != NULL);
	
	free_env_list(env_list);
	printf("delete_env_node tests passed!\n\n");
}

void	test_get_set_env_value(void)
{
	printf("=== Testing get/set_env_value ===\n");
	
	t_env *env_list = NULL;
	
	set_env_value(&env_list, "TEST_VAR", "test_value");
	char *value = get_env_value(env_list, "TEST_VAR");
	assert(value != NULL);
	assert(ft_strncmp(value, "test_value", 11) == 0);
	
	set_env_value(&env_list, "TEST_VAR", "new_value");
	value = get_env_value(env_list, "TEST_VAR");
	assert(value != NULL);
	assert(ft_strncmp(value, "new_value", 10) == 0);
	
	value = get_env_value(env_list, "NONEXISTENT");
	assert(value == NULL);
	
	free_env_list(env_list);
	printf("get/set_env_value tests passed!\n\n");
}

void	test_array_conversion(void)
{
	printf("=== Testing array conversion ===\n");
	
	char *test_envp[] = {
		"PATH=/usr/bin:/bin",
		"HOME=/home/user",
		"USER=testuser",
		NULL
	};
	
	t_env *env_list = array_to_env_list(test_envp);
	assert(env_list != NULL);
	
	char *value = get_env_value(env_list, "PATH");
	assert(value != NULL);
	assert(ft_strncmp(value, "/usr/bin:/bin", 14) == 0);
	
	value = get_env_value(env_list, "HOME");
	assert(value != NULL);
	assert(ft_strncmp(value, "/home/user", 11) == 0);
	
	char **new_envp = env_list_to_array(env_list);
	assert(new_envp != NULL);
	assert(new_envp[0] != NULL);
	assert(new_envp[1] != NULL);
	assert(new_envp[2] != NULL);
	assert(new_envp[3] == NULL);
	
	int i = 0;
	while (new_envp[i])
	{
		free(new_envp[i]);
		i++;
	}
	free(new_envp);
	free_env_list(env_list);
	
	printf("array conversion tests passed!\n\n");
}

int	main(void)
{
	printf("Starting environment utility tests...\n\n");
	
	test_create_env_node();
	test_add_env_node();
	test_find_env_node();
	test_delete_env_node();
	test_get_set_env_value();
	test_array_conversion();
	
	printf("All environment utility tests passed!\n");
	return (0);
}
