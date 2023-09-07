/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:23 by makbas            #+#    #+#             */
/*   Updated: 2023/09/07 16:51:59 by makbas           ###   ########.fr       */
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
    int     i;
    int     len;

    len = 0;
    while (env[len])
        len++;
    m_shell.env = ft_calloc(sizeof(char *), len + 1);
    i = 0;
    while (i < len)
    {
        m_shell.env[i] = env[i];
        i++;
    }
}

void    append_paths()
{
    char    *path;

    path = m_shell.env[2] + 5;
    m_shell.paths = ft_split(path, ':');
}