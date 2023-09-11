/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:32 by makbas            #+#    #+#             */
/*   Updated: 2023/09/11 19:51:03 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	m_shell;

void	start_cmd(void)
{
	t_process	*process;

	process = m_shell.process;
	if (is_builtin(process->execute[0]) && m_shell.process_count == 1)
	{
		run_builtin(process);
	}
	
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_env(env);
	printf("\n%s\n", WELCOME);
	while (ac && av)
	{
		input = readline(YELLOW"MINISHELL>> : "RESET);
		if (*input)
		{
			m_shell.process_count = 0;
			m_shell.token = NULL;
			m_shell.process = NULL;
			tokenize(input);
			if (!lexerize())
				return (0);
			start_cmd();
			free_process();
			add_history(input);
		}
		free(input);
	}
	exit(errno);
}
