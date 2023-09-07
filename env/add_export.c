/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:05:41 by makbas            #+#    #+#             */
/*   Updated: 2023/09/07 19:09:00 by rdemiray         ###   ########.fr       */
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