/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:00:32 by makbas            #+#    #+#             */
/*   Updated: 2023/09/06 19:05:55 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	m_shell;

void	start_cmd()
{
	t_process	*process;

	process = m_shell.process;
	if (is_builtin(process->execute[0]) && m_shell.process_count == 1)
	{
		run_builtin(process);
	}
	
}

void print_token_sequence(t_minishell *m_shell)
{
    char **current_token = m_shell->paths;
    
    printf("Token Sequence:\n");
    int i = 0;
    while (current_token[i] != NULL)
    {
        printf("Token Type: %s\n", current_token[i]);
		i++;

    }
}

void print_token_sequence2(t_minishell *m_shell)
{
    char **current_token = m_shell->process->execute;
    char **current_token2 = m_shell->process->redirects;
    int i = 0;
    while (current_token[i] != NULL)
    {
        printf("exe: %s\n", current_token[i]);
		i++;
    }
	i = 0;
    while (current_token2[i] != NULL)
    {
        printf("red: %s\n", current_token2[i]);
		i++;
    }
}


int main(int ac, char **av, char **env)
{
    char *input;
	
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
			print_token_sequence2(&m_shell);
			start_cmd();
			free_process();
			add_history(input);
			
		}
		free(input);
	}
	exit(errno);
}
