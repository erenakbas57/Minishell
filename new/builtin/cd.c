/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:18:13 by makbas            #+#    #+#             */
/*   Updated: 2023/08/31 18:01:50 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     b_cd()
{
    char  *arg;

    arg = m_shell.process->execute[1];
    if (arg == NULL) {
        chdir(getenv("HOME"));
        return 0;
    }
    if (chdir(arg) != 0) {
        printf(MAGENTA"Minishell: "RED);
        printf("CD: "RESET);
        printf("No such file or directory\n");
        return 1;
    }
    return 0;
}