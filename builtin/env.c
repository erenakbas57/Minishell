/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:06:24 by makbas            #+#    #+#             */
/*   Updated: 2023/09/07 19:07:10 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    env_write(char* str)
{
    int i;
    char* path;
    t_env   *env;
    
    i = 0;
    str = ft_strjoin(str, "=");
    env = m_shell.env;
    while (env)
    {
        if (ft_strncmp(env->str, str, ft_strlen(str)) == 0)
        {
            path = env->str;
            str = ft_substr(path, ft_strlen(str), ft_strlen(path) - ft_strlen(str));
            printf("%s\n", str);
            return ;
        }
        env = env->next;
    }
    printf(MAGENTA"ENV: "RED);
    printf("%s: "RESET, m_shell.process->execute[1]);
    printf("No such file or directory\n");
}

int b_env()
{
    t_env   *env;
    char    **exe;

    env = m_shell.env;
    exe = m_shell.process->execute;
    if (exe[1] == NULL)
    {
        while (env)
        {
            printf("%s\n", env->str);
            env = env->next;
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