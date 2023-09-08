/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:33:07 by makbas            #+#    #+#             */
/*   Updated: 2023/09/08 18:26:48 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int b_exit()
{
    char    **exe;
    int count;
    
    exe = m_shell.process->execute;
    count = 0;
    while (exe[count])
        count++;
    if ((count == 1) || (count == 2 && is_number(exe[1])))
    {
        printf("exit\n");
        exit(0);
    }
    else if ((count == 2) && !(is_number(exe[1])))
    {
        printf("exit\n");
        printf(GREEN"Minishell: "MAGENTA);
        printf("exit: "RED);
        printf("%s: "RESET, exe[1]);
        printf("numeric argument required\n");
        exit(0);
    }
    else if (count > 2)
    {
        printf("exit\n");
        printf(GREEN"Minishell: "MAGENTA);
        printf("exit: "RESET);
        printf("too many arguments\n");
        exit(0);
    }
    return (0);
}