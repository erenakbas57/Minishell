/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:42:33 by makbas            #+#    #+#             */
/*   Updated: 2023/08/15 19:56:03 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     quote_control(char *quote)
{
    int count;
    int i;
    int finish;

    finish = 0;
    i = 0;
    count = 0;
    while (quote[i])
    {
        if (quote[i] == SINGLE_QUOTE)
            count++;
        i++;
    }
    if (count % 2 == 1)
    {
        printf("%d  tırnak sayısı****\n\n", count);
        return (1);
    }
    i = 0;
    while (quote[i] != DOLLAR)
    {
        if (quote[i] == SINGLE_QUOTE)
            finish++;
        i++;
    }
    if (((count - finish) % 2) == 1)
    {
        printf("%d  dolara kadar olan tırnak sayısı****\n\n", finish);
        return (1);
    }
    return (0);
}

int     using_control(char* str)
{
    if (str[0] == SINGLE_QUOTE && quote_control(str))
        return (0);
    int i;
    
    
    i = 0;
    while (str[i] != DOLLAR)
        i++;
    i++;
    
    return (0);
}


char*   dollar_control(char* token)
{
    char*   new_str;

    new_str = token;
    if (ft_strchr(new_str, DOLLAR) && using_control(new_str))
    {
        return (new_str);
    }
    
    return (new_str);
}