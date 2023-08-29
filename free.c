/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:25:54 by makbas            #+#    #+#             */
/*   Updated: 2023/08/26 17:26:38 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process(void)
{
	t_process	*tmp;
	t_process	*process;

	process = m_shell.process;
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