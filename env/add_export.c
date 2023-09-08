/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:05:41 by makbas            #+#    #+#             */
/*   Updated: 2023/09/08 17:40:01 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    add_export()
{
    t_env   *env;

    env = m_shell.env;
    while (env)
    {
        export_add_back(&m_shell.export, \
            new_export(ft_strjoin_two(env->str)));
        env = env->next;
    }
}