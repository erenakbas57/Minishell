/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:20:09 by makbas            #+#    #+#             */
/*   Updated: 2023/09/08 18:26:17 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     export_control(char *str)
{
    int i;
    int equal_i;
    int len;
    int value;
    
    len = ft_strlen(str);
    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            equal_i = i;
        i++;
    }
    if (!(equal_i >= 1))
        equal_i = -1;
    value = -1;
    if ((str[0] >= '0' && str[0] <= '9') == 1)
        value = ERROR;
    else if (equal_i == -1)
        value = VARIABLE;
    else if (equal_i + 1 == len)
        value = EQUAL;
    else if (equal_i + 1 < len)
        value = VALUE;
    return (value);
}

void    new_value_export(char *new, int choose)
{
    if (choose == VARIABLE)
        export_add_back(&m_shell.export, new_export(ft_strdup_two(new, 12, VARIABLE)));
    else if (choose == EQUAL)
    {
        export_add_back(&m_shell.export, new_export(ft_strdup_two(new, 14, EQUAL)));
        env_add_back(&m_shell.env, new_env(ft_strdup(new)));
    }
    else if (choose == VALUE)
    {
        export_add_back(&m_shell.export, new_export(ft_strjoin_two(new)));
        env_add_back(&m_shell.env, new_env(ft_strdup(new)));
    }
}

void    show_export()
{
    t_export    *exp;

    exp = m_shell.export;
    while (exp)
    {
        printf("%s\n", exp->str);
        exp = exp->next;
    }
}

int     b_export(char **exe)
{
    int     i;
    int     choose;
    int     error;
    char    **cpy_exe;

    cpy_exe = exe;
    error = 0;
    if (count_value(exe) == 1)
        show_export();
    else 
    {
        i = 1;
        while (cpy_exe[i])
        {
            choose = export_control(cpy_exe[i]);
            if (choose == ERROR)
                error++;
            else if (choose == VARIABLE)
                new_value_export(cpy_exe[i], VARIABLE);
            else if (choose == EQUAL)
                new_value_export(cpy_exe[i], EQUAL);
            else if(choose == VALUE)
                new_value_export(cpy_exe[i], VALUE);
            i++;
        }
    }
    if (error > 0)
        printf("hata\n");
    return (0);
}
