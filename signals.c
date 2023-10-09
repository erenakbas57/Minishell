/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:00:18 by makbas            #+#    #+#             */
/*   Updated: 2023/10/09 16:31:56 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_parent(void)
{
	return (g_mshell.parent_pid);
}

void	sig_quit_handler(int signum)
{
	(void)signum;
	if (g_mshell.quit == 0)
	{
		write(1, "\033[2D", 4);
		write(1, "$ ", 2);
	}
	else
	{
		write(1, "\033[2D", 4);
		write(1, "  ", 2);
		write(1, "\033[2D", 4);
	}
	g_mshell.quit++;
	rl_redisplay();
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_mshell.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(char *input)
{
	if (!input)
	{
		printf("\n");
		printf("\033[A");
		printf("MinisHELL$ ");
		printf("exit\n");
		exit(errno);
	}
}
