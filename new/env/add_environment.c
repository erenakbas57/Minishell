/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:23 by makbas            #+#    #+#             */
/*   Updated: 2023/09/09 14:27:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	init_env(char **env)
{
	append_env(env);
    add_export();
	append_paths();
}

int     count_value(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    append_env(char **env)
{
    int         i;
    
    i = 0;
    while (env[i])
    {
        env_add_back(&m_shell.env, new_env(ft_strdup(env[i])));
        i++;
    }
}

void    append_paths()
{
    char    *path;

    path = (m_shell.env->next->next->str) + 5;
    m_shell.paths = ft_split(path, ':');
}