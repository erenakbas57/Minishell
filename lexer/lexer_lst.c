/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 00:01:39 by makbas            #+#    #+#             */
/*   Updated: 2023/08/01 14:47:57 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_process    *process_init()
{
	t_process	*process;

	process = ft_calloc(sizeof(t_process), 1);
	pipe(process->fd);
	process->pid = -1;
	process->execute = ft_calloc(sizeof(char *), 1);
	process->redirects = ft_calloc(sizeof(char *), 1);
	process->prev = NULL;
	process->next = NULL;
	return (process);
}

t_process	*last_process(t_process *process)
{
	if (!process)
		return (0);
	while (process->next != 0)
		process = process->next;
	return (process);
}

void	process_add_back(t_process **process, t_process *new)
{
	t_process	*i_process;

	i_process = *process;
	if (!(i_process))
		*process = new;
	else
	{
		while (i_process->next)
			i_process = i_process->next;
		i_process->next = new;
		new->prev = i_process;
	}
}