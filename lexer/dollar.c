/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:42:33 by makbas            #+#    #+#             */
/*   Updated: 2023/08/20 17:38:46 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     env_add(char** env)
{
    int i;
    char* path;
    
    i = 0;
    while (m_shell.env[i])
    {
        if (ft_strncmp(m_shell.env[i], *env, ft_strlen(*env)) == 0)
        {
            path = m_shell.env[i];
            *env = ft_substr(path, ft_strlen(*env) + 1, ft_strlen(path) - ft_strlen(*env));
            return (0);
        }
        i++;
    }
    return (1);
}

int     env_control(char* str)
{
    int     i;
    int     len;
    int     start;
    char*   env;
    
    i = 0;
    len = 0;
    while (str[i] != '\0' && str[i] != DOLLAR)
        i++;
    i++;
    start = i;
    while (str[i] && is_char(str[i]))
    {
        i++;
        len++;
    }
    env = ft_substr(str, start, len);
    
    if (env_add(&env))
        return (0);
    return (1);
}

int     using_control(char* quote)
{
    int count;
    int i;
    int start;
    int finish;

    start = 0;
    finish = 0;
    i = 0;
    count = 0;
    while (quote[i] != DOLLAR)
    {
        if (quote[i] == SINGLE_QUOTE)
            start++;
        i++;
    }
    while (quote[i])
    {
        if (quote[i] == SINGLE_QUOTE)
            finish++;
        i++;
    }
    count = start + finish;
    if ((count == 2 && start == 1) || ((start != finish) && (start % 2 == 1)))
        return (0);
    if (env_control(quote))
        return (0);
    return (1);
}


char*   dollar_control(char* token)
{
    char*   new_str;

    new_str = token;
    if (ft_strchr(new_str, DOLLAR) && using_control(new_str))
    {   
        char*   word_one;
        int     i;

        i = 0;
        while(new_str[i] != DOLLAR)
            i++;
        word_one = ft_substr(new_str, 0, i);
        
        return (new_str);
    }
    return (new_str);
}