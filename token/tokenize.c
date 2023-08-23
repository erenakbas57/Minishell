/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:08:12 by makbas            #+#    #+#             */
/*   Updated: 2023/08/23 09:14:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    end_token(char **str, char type)
{
	(*str)++;
	while (**str)
	{
		if (**str == type)
        {
            (*str)++;
			if (is_whitespace(**str) || is_redirects(*str))
				break ;
			else
				while (**str && !is_whitespace(**str) && !is_redirects(*str))
					(*str)++;
			return ;
        }
		(*str)++;
	}
}

int    end_token_two(char *str)
{
    int i;

    i = 1;
    while (str[i])
    {
        if (str[i] == DOUBLE_QUOTE || str[i] == SINGLE_QUOTE)
            return (i);
        else if (is_whitespace(str[i]))
            return (i);
        i++;
    }
    return (i);
}

void     parse_string(char **str)
{
    char    *new;
    char    *token;
    int     len;
    
    while (**str && is_whitespace((**str)))
        (*str)++;
    new = *str;
    if (**str && **str == DOUBLE_QUOTE)
        end_token(str, DOUBLE_QUOTE);
    else if (**str && **str == SINGLE_QUOTE)
        end_token(str, SINGLE_QUOTE);
    else
        *str += end_token_two(*str);
    len = *str - new;
    if (len > 0)
    {
        token = ft_substr(new, 0, len);
        token_add_back(&m_shell.token, new_token(token, STRING), 0);
    }
    while (**str && is_whitespace((**str)))
        (*str)++;
}

void print_tokens(t_token *token) {
    while (token) {
        printf("-%s-\n", token->str);
        token = token->next;
    }
}

void    tokenize(char *input)
{
    while (*input)
    {
        if (is_redirects(input) == RED_APPEND)
            input += token_add_back(&m_shell.token, new_token(ft_strdup(">>"), RED_APPEND), 2);
		else if (is_redirects(input) == HERE_DOC)
            input += token_add_back(&m_shell.token, new_token(ft_strdup("<<"), HERE_DOC), 2);
		else if (is_redirects(input) == RED_OUTPUT)
            input += token_add_back(&m_shell.token, new_token(ft_strdup(">"), RED_OUTPUT), 1);
		else if (is_redirects(input) == RED_INPUT)
            input += token_add_back(&m_shell.token, new_token(ft_strdup("<"), RED_INPUT), 1);
		else if (is_redirects(input) == PIPE)
            input += token_add_back(&m_shell.token, new_token(ft_strdup("|"), PIPE), 1);
		else
            parse_string(&input);
    }
    //print_tokens(m_shell.token);
}

