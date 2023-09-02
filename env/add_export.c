/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:05:41 by makbas            #+#    #+#             */
/*   Updated: 2023/09/02 17:50:40 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char*     env_value(char* env)
{
    int     i;
    int     x;
    char*   path;
    
    i = 0;
    x = 0;
    while (env[x] != '=')
        x++;
    env = ft_substr(env, 0, x);
    while (m_shell.env[i])
    {
        if (ft_strncmp(m_shell.env[i], env, ft_strlen(env)) == 0)
        {
            path = m_shell.env[i];
            env = ft_substr(path, ft_strlen(env) + 1, ft_strlen(path) - ft_strlen(env));
            return (env);
        }
        i++;
    }
    return (NULL);
}

char    **env_quote(char **env)
{
    int     i;
    int     x;
    char    *first;
    char    **new;
    char    **cpy_env;

    cpy_env = env;
    i = 0;
    new = ft_calloc(sizeof(char *), (count_value(env) + 1));
    while (env[i])
    {
        first = NULL;
        x = 0;
        while (env[i][x] != '=')
            x++;
        first = malloc(ft_strlen(env[i]) + 3);
        first = ft_strlcpy(first, env[i], x + 2);
        first = ft_strjoin(first, "\"");
        first = ft_strjoin(first, env_value(cpy_env[i]));
        first = ft_strjoin(first, "\"");
        first[ft_strlen(env[i]) + 3] = '\0';
        new[i] = first;
        free(first);
        i++;
    }
    free(cpy_env);
    return (new);
}

void    add_export(int size)
{
    char    **env;
    int     len;
    int     i;

    len = 0;
    while (m_shell.env[len])
        len++;
    if (size == 0)
        size = len + 1;
    m_shell.export = ft_calloc(sizeof(char *), size);
    env = env_quote(m_shell.env);
    i = 0;
    while (i < len)
    {
        m_shell.export[i] = env[i];
        i++;
        //free(env[i]);
    }
    //free(env);
}