/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:18:00 by makbas            #+#    #+#             */
/*   Updated: 2023/09/18 14:11:09 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	run_cmd(t_process *process)
{
	pid_t	pid;
	char	*path;
	int		count;

	count = 1;
	pid = fork();
	if (pid == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		// signal(SIGINT, SIG_DFL);
		// cmd_route(process);
		// run_builtin(process->execute, 0);
		path = get_path(process->execute[0]);
		execve(path, process->execute, NULL);
		// command_err(process->execute[0]);
		// exit(errno);
	}
	else
	{
		process->pid = pid;
		if (count == 1)
			g_mshell.parent_pid = pid - 1;
	}
}