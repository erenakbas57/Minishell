/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:23 by makbas            #+#    #+#             */
/*   Updated: 2023/09/02 17:56:26 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	init_env(char **env)
{
	append_env(env, 0);
    add_export(0);
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

void    append_env(char **env, int size)
{
    int     i;
    int     len;

    len = 0;
    while (env[len])
        len++;
    printf("%d\n", len);
    if (size == 0)
        size = len + 1;
    m_shell.env = ft_calloc(sizeof(char *), size);
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