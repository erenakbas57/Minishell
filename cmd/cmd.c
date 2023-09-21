/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:18:00 by makbas            #+#    #+#             */
/*   Updated: 2023/09/21 14:26:08 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_route(t_process *process)
{
	if (process->prev == NULL)
		dup2(process->fd[1], 1);
	else if (process->next == NULL)
		dup2(process->prev->fd[0], 0);
	else
	{
		dup2(process->prev->fd[0], 0);
		dup2(process->fd[1], 1);
	}
}

void	heredoc_route(t_process *process)
{
	dup2(process->heredoc_fd[0], 0); // 0'dan gelenleri heredoc_fd'de depolicak
	if (process->next != NULL)
		dup2(process->fd[1], 1); //1_den gelenleri fd'de depolicak
}

void	cmd_route(t_process *process)
{
	if (g_mshell.process_count > 1)
	{
		if (contain_heredoc(process))
			heredoc_route(process);
		else
			pipe_route(process);
	}
	get_inputs(process);
	set_outputs(process);
	close_all_fd();
}


void get_builtin(t_process *process)
{
	int input;
	int output;
	
	input = dup(0);
	output = dup(1);
	get_inputs(process);
	set_outputs(process);
	run_builtin(process);
	dup2(input, 0);
	dup2(output, 1);
	close(input);
	close(output);
}

void	run_cmd(t_process *process)
{
	pid_t	pid;
	char	*path;
	int		count;
	char	**env;
	
	count = 1;
	pid = fork();
	env = append_envo();
	if (pid == CHILD_PROCESS)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		cmd_route(process);
		run_builtin(process);
		path = get_path(process->execute[0]);
		//printf("path: %s\n",path);
		execve(path, process->execute, env);
		command_error(process->execute[0]);
		exit(errno);
	}
	else
	{
		process->pid = pid;
		if (count == 1)
			g_mshell.parent_pid = pid - 1;
	}
	free(env);
}