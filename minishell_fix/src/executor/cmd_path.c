/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:06:49 by yuhashim          #+#    #+#             */
/*   Updated: 2025/05/31 19:06:49 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "error.h"
#include <sys/stat.h>

static char	*check_direct_path(const char *cmd)
{
	struct stat	file_stat;

	if (stat(cmd, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (ft_strdup("is_directory"));
		else if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (ft_strdup("permission_denied"));
	}
	else
		return (ft_strdup("no_such_file"));
}

static char	*check_path_executable(const char *dir, const char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = check_path_executable(paths[i], cmd);
		if (full_path)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(const char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
		return (check_direct_path(cmd));
	path_env = get_env_value(shell->env_list, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = search_in_paths(paths, cmd);
	free_split(paths);
	return (full_path);
}
