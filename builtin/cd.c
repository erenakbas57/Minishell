/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:18:13 by makbas            #+#    #+#             */
/*   Updated: 2023/09/18 11:49:24 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_cd()
{
	char	*arg;

	arg = g_mshell.process->execute[1];
	if (arg == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	if (chdir(arg) != 0)
	{
		printf("Minishell: ");
		printf("CD: ");
		printf("No such file or directory\n");
		return (1);
	}
	return (0);
}