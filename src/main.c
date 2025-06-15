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

void minihell_loop(char **envp)
{
    char *line;
    init_signal();
    while(1)
    {
        line = readline("minishell$ ");
        if(!line)
        {
            ft_putstr_fd("\033[1A\033[11C", 0);
            ft_putstr_fd("exit\n", 0);
            break;
        }
        if(*line)
            add_history(line);
        /*
        parserの関数
        */
        ex_main();
    }
}

int main(int argc, char **argv, char **envp)
{
    char **new_envp;
    (void)argv;
    
    g_shell_mode = MODE_INTERACTIVE;
    if(argc != 1)
    {
        printf("No arguments required\n");
        exit (1);
    }
    new_envp = dup_envp(envp);
    minishell_loop(new_envp);
    return (0);
}