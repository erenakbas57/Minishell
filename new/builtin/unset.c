/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:39:00 by makbas            #+#    #+#             */
/*   Updated: 2023/09/09 18:50:16 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//str_cmp için iki yeni fonk ekledim sona 

void env_lst_delone(char *str)
{
	t_env *env_node;
	t_env *temp;
	char *env_str;

	env_node = m_shell.env;

	if (!env_node)
		return;
	while (env_node->next)
	{
		env_str = env_node->next->str;
		if (ft_strcmp_env2(env_str, str))
		{
			temp = env_node->next;
			env_node->next = env_node->next->next;
			free(temp->str);
			free(temp);
			break; 
		}
		env_node = env_node->next;
	}
}

void export_lst_delone(char *str)
{
	t_export *export_node;
	t_export *temp;
	char *node_str;

	export_node = m_shell.export;

	if (!export_node)
		return;
	while (export_node->next)
	{
		node_str = export_node->next->str;
		if (ft_strcmp_export(node_str, str))
		{
			temp = export_node->next;
			export_node->next = export_node->next->next;
			free(temp->str);
			free(temp);
			break; 
		}
		export_node = export_node->next;
	}
}


int unset_control(char *str)
{
	int i;
	int len;
	int equal_i;
	int value;
	
	i = 0;
	len = ft_strlen(str);
	equal_i = 0;
	while (str[i])
    {
        if (str[i] == '=')
            equal_i = i;
        i++;
    }
    value = -1;
    if ((str[0] >= '0' && str[0] <= '9') == 1)
        value = ERROR;
    else if (equal_i == 0)
        value = VARIABLE;
    else if (equal_i + 1 == len)
        value = EQUAL;
    else if (equal_i + 1 < len)
        value = VALUE;
    return (value);
}


int b_unset(char **exe)
{
    int i;
	int choose;
	int error;
	
	error = 0;
	if(count_value(exe) >= 2)
	{
		i = 1;
		while(exe[i])
		{
			choose = unset_control(exe[i]);
			if(choose == VARIABLE)
			{
				export_lst_delone(exe[i]);
				env_lst_delone(exe[i]);
			}
			else
				error++;
			i++;
		}
	}
	if(error > 0)
		printf("error\n");
	return(0);
}