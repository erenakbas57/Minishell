/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:05:41 by makbas            #+#    #+#             */
/*   Updated: 2023/09/03 19:12:59 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    add_export()
{
    int     len;

    len = 0;
    while (m_shell.env[len])
        len++;
    m_shell.export = ft_calloc(sizeof(char *), len + 1);
    int i = 0;
    while (i < len)
    {
        m_shell.export[i] = ft_strjoin_two(m_shell.env[i]);
        i++;
    }
}