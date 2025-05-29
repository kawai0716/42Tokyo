/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:02:08 by marvin            #+#    #+#             */
/*   Updated: 2025/05/27 18:02:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **dup_envp(char **envp)
{
    int i;
    char **new_envp;

    i = 0;
    while (envp[i])
        i++;
    new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
    if(!new_envp)
    {
        perror("malloc_error");
        return (NULL);
    }
    i = 0;
    while(envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        if(!new_envp[i])
        {
            perror("malloc_error");
            while (i > 0)
            {
                i--;
                free(new_envp[i]);
            }
            free(new_envp);
            return (NULL);
        }
        i++;
    }
    return (new_envp);
}

int main(int argc, char **argv, char **envp)
{
    char **env;
    (void)argv;
    
    if(argc != 1)
    {
        printf("No arguments required\n");
        return (1);
    }
    env = dup_envp(envp);
    
    return (0);
}