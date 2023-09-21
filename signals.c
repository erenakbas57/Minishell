/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:00:18 by makbas            #+#    #+#             */
/*   Updated: 2023/09/21 15:13:56 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	sig_quit_handler(int signum)
{
	(void)signum;
	
	signal(SIGQUIT, SIG_IGN);
	write(1, "\e[8me\e", 6);
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
		printf("Minishell>> : ");
		printf("exit\n");
		exit(errno);
	}
}