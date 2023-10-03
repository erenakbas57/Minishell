/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:25:54 by makbas            #+#    #+#             */
/*   Updated: 2023/10/02 13:13:32 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process(void)
{
	t_process	*tmp;
	t_process	*process;

	process = g_mshell.process;
	if (!process)
		return ;
	while (process)
	{
		free_array(process->execute);
		free_array(process->redirects);
		tmp = process;
		process = process->next;
		free(tmp);
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_token(void)
{
	t_token		*tmp;
	t_token		*token;

	token = g_mshell.token;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = g_mshell.token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
