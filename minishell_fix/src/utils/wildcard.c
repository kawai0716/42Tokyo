/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhashim <yuhashim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 05:54:21 by yuhashim          #+#    #+#             */
/*   Updated: 2025/06/21 05:54:21 by yuhashim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <dirent.h>
#include <sys/stat.h>

static int	is_match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		if (is_match(pattern + 1, str))
			return (1);
		if (*str != '\0' && is_match(pattern, str + 1))
			return (1);
		return (0);
	}
	if (*str != '\0' && (*pattern == *str || *pattern == '?'))
		return (is_match(pattern + 1, str + 1));
	return (0);
}

static int	process_dir_entry(struct dirent *entry, const char *pattern,
							char **result, int *count)
{
	if (entry->d_name[0] == '.')
		return (0);
	if (is_match(pattern, entry->d_name))
	{
		result[*count] = ft_strdup(entry->d_name);
		(*count)++;
	}
	return (1);
}

static char	**process_directory_entries(DIR *dir, const char *pattern,
									char **result)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		process_dir_entry(entry, pattern, result, &count);
		entry = readdir(dir);
	}
	result[count] = NULL;
	if (count == 0)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static char	**expand_wildcard_simple(const char *pattern)
{
	DIR				*dir;
	char			**result;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	result = malloc(sizeof(char *) * 1000);
	if (!result)
	{
		closedir(dir);
		return (NULL);
	}
	result = process_directory_entries(dir, pattern, result);
	closedir(dir);
	return (result);
}

char	*expand_wildcard(const char *word)
{
	char	**matches;
	char	*result;
	int		i;

	if (!ft_strchr(word, '*') && !ft_strchr(word, '?'))
		return (ft_strdup(word));
	matches = expand_wildcard_simple(word);
	if (!matches)
		return (ft_strdup(word));
	result = ft_strdup(matches[0]);
	i = 1;
	while (matches[i])
	{
		result = expand_match_result(result, matches[i]);
		i++;
	}
	free(matches[0]);
	free(matches);
	return (result);
}
