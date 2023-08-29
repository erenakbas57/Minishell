/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:14:22 by makbas            #+#    #+#             */
/*   Updated: 2023/08/26 17:37:36 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char*     env_add(char* env)
{
    int i;
    char* path;
    
    i = 0;
    env = ft_strjoin(env, "=");
    while (m_shell.env[i])
    {
        if (ft_strncmp(m_shell.env[i], env, ft_strlen(env)) == 0)
        {
            path = m_shell.env[i];
            env = ft_substr(path, ft_strlen(env), ft_strlen(path) - ft_strlen(env));
            return (env);
        }
        i++;
    }
    
    return ("$");
}

int     env_control(char* token, char** str, int* i)
{
    int     len;
    int     start;
    char*   env;
    
    len = 0;
    start = *i;
    while (token[*i] && is_char(token[*i]))
    {
        (*i)++;
        len++;
    }
    env = ft_substr(token, start, len);
    len = ft_strlen(env) + 1;
    env = env_add(env);
    if (env[0] != DOLLAR)
        *str = ft_strjoin(*str, env);
    return (len);
}

int     quote_control(char* quote)
{
    int count;
    int i;
    int start;
    int finish;

    start = 0;
    finish = 0;
    i = -1;
    count = 0;
    while (quote[i++] != DOLLAR)
    {
        if (quote[i] == SINGLE_QUOTE)
            start++;
    }
    while (quote[i++])
    {
        if (quote[i] == SINGLE_QUOTE)
            finish++;
    }
    count = start + finish;
    if (((count % 2 == 0) && (start % 2 == 1)) || ((finish == 1) && (start == 1)))
        return (0);
    if (count == 0)
        return (1);
    return (1);
}


char*   dollar_control(char* token)
{
    if (ft_strchr(token, DOLLAR) && quote_control(token))
    {   
        int     token_i;
        int     str_i;
        char*   str;
        
        token_i = 0;
        str_i = 0;
        str = ft_calloc(ft_strlen(token), sizeof(char*));
        while (token[token_i])
        {
            if (token[token_i] == DOLLAR)
            {
                token_i++;
                env_control(token, &str, &token_i);
                str_i = ft_strlen(str);
            }
            else
            {
                str[str_i] = token[token_i];
                str_i++;
                token_i++;
            }
        }
        return (str);
    }
    token = ft_strdup(token);
    return (token);
}