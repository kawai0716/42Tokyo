/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:47:54 by marvin            #+#    #+#             */
/*   Updated: 2025/06/12 12:47:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int read_heredoc_to_pipe(const char *finish_str)
{
    int fd[2];
    char *line;
    int ret;

    if (pipe(fd) < 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, finish_str) == 0)
        {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    return (fd[0]);
}
