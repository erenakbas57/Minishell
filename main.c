/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:32 by makbas            #+#    #+#             */
/*   Updated: 2023/09/21 15:03:03 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_cmd(void)
{
	t_process	*process;

	process = g_mshell.process;
	close_all_fd();
	while (process)
	{
		if (process->pid != -1)
		{
			waitpid(process->pid, &errno, 0);
			errno = WEXITSTATUS(errno);
		}
		process = process->next;
	}
}

void	init_env(char **env)
{
	pid_t	child_pid;

	errno = 0;
	g_mshell.paths = NULL;
	append_env(env);
	append_export();
	append_paths();
	child_pid = fork();
	if (child_pid == 0)
		exit(1);
	else
	{
		g_mshell.parent_pid = child_pid - 1;
		wait(NULL);
	}
}

void	start_cmd(void)
{
	t_process	*process;

	process = g_mshell.process;
	if (!process)
		return ;
	is_heredoc();
	if (g_mshell.ignore)
		return (close_all_fd());
	if (is_builtin(process->execute[0]) && g_mshell.process_count == 1)
	{
		get_builtin(process);
		process = process->next;
	}
	while (process)
	{
		run_cmd(process);
		process = process->next;
	}
	wait_cmd();
}

void	launch_ms(char *input)
{
	g_mshell.process_count = 0;
	g_mshell.token = NULL;
	g_mshell.process = NULL;
	tokenize(input);
	if (!lexerize())
		return ;
	start_cmd();
	free_process();
	add_history(input);
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_env(env);
	while (ac && av)
	{
		g_mshell.ignore = FALSE;
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, sig_quit_handler);

		input = readline("MINISHELL>> : ");
		ctrl_d(input);
		if (g_mshell.ignore)
		{
			free(input);
			input = malloc(1);
			errno = 1;
		}
		if (*input)
			launch_ms(input);
		free(input);
	}
	exit(errno);
}
