/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:06:24 by makbas            #+#    #+#             */
/*   Updated: 2023/08/31 19:14:44 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    env_write(char* str)
{
    int i;
    char* path;
    
    i = 0;
    str = ft_strjoin(str, "=");
    while (m_shell.env[i])
    {
        if (ft_strncmp(m_shell.env[i], str, ft_strlen(str)) == 0)
        {
            path = m_shell.env[i];
            str = ft_substr(path, ft_strlen(str), ft_strlen(path) - ft_strlen(str));
            printf("%s\n", str);
            return ;
        }
        i++;
    }
    printf(MAGENTA"ENV: "RED);
    printf("%s: "RESET, m_shell.process->execute[1]);
    printf("No such file or directory\n");
}

int b_env()
{
    char    **env;
    char    **exe;
    int     i;
    
    i = 0;
    env = m_shell.env;
    exe = m_shell.process->execute;
    if (exe[1] == NULL)
    {
        while (env[i])
        {
            printf("%s\n", env[i]);
            i++;
        }
    }
    else if (exe[1] != NULL && exe[2] == NULL)
    {
        env_write(exe[1]);
    }
    else
    {
        printf(CYAN"usage: "RESET);
        printf("pwd [-L | -P]: \n");
    }
    return (0);
}