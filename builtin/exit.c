/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:33:07 by makbas            #+#    #+#             */
/*   Updated: 2023/09/19 16:48:17 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_exit(void)
{
	char	**exe;
	int		count;

	exe = g_mshell.process->execute;
	count = 0;
	while (exe[count])
		count++;
	if ((count == 1) || (count == 2 && !(is_number(exe[1]))))
	{
		printf("exit\n");
		exit(errno);
	}
	else if ((count == 2) && !(is_number(exe[1])))
	{
		printf("değer: %s\n", exe[1]);
		printf("exit\n");
		printf("Minishell: ");
		printf("exit: ");
		printf("%s: ", exe[1]);
		printf("numeric argument required\n");
		exit(0);
	}
	else if (count > 2)
	{
		errno = 1;
		printf("exit\n");
		printf("Minishell: ");
		printf("exit: ");
		printf("too many arguments\n");
		exit(0);
	}
	return (0);
}