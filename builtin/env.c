/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:06:24 by makbas            #+#    #+#             */
/*   Updated: 2023/08/29 16:44:41 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int b_env()
{
    char    **env;
    int     i;
    
    i = 0;
    env = m_shell.env;
    if (m_shell.process->execute[1] != NULL)
    {
        printf(MAGENTA"ENV: "RED);
        printf("%s: "RESET, m_shell.process->execute[1]);
        printf("No such file or directory\n");
    }
    else
    {
        while (env[i])
        {
            printf("%s\n", env[i]);
            i++;
        }
    }
    return (0);
}