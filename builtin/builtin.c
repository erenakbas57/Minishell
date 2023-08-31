/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:00:25 by makbas            #+#    #+#             */
/*   Updated: 2023/08/31 18:15:32 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     is_builtin(char *input)
{
    char    **cmd;
    int     i;
    
    cmd = malloc(sizeof(char *) * 8);
    cmd[0] = "CD";
    cmd[1] = "EXIT";
    cmd[2] = "UNSET";
    cmd[3] = "EXPORT";
    cmd[4] = "ENV";
    cmd[5] = "PWD";
    cmd[6] = "ECHO";
    cmd[7] = NULL;
    i = 0;
    while (i < 7)
    {
        if (ft_strcmp(cmd[i], input))
        {
            free(cmd);
            return(1);
        }
        i++;
    }
    free(cmd);
    return (0);
}

void    run_builtin(t_process *process)
{
    char    *exe;
    char    **input;
    
    exe = process->execute[0];
    input = process->execute;
    if (ft_strcmp(exe, "CD"))
        b_cd();
    if (ft_strcmp(exe, "PWD"))
        b_pwd();
    if (ft_strcmp(exe, "EXIT"))
        b_exit();
    if (ft_strcmp(exe, "ENV"))
        b_env();
    if (ft_strcmp(exe, "ECHO"))
        b_echo(input);
}