/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:12:44 by makbas            #+#    #+#             */
/*   Updated: 2023/09/18 17:49:15 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(STDOUT_FILENO, &(input[i]), 1);
		i++;
	}
}

int	echo_parameter(char **prm)
{
	int	i;
	int	j;
	
	i = 1;
	while (prm[i])
	{
		j = 1;
		if (prm[i][0] != '-')
		{
			while (prm[i][j] != '\0')
			{
				if (prm[i][j] != 'n')
					return (i);
				j++;
			}
		}
		i++;
	}
	return (i);
}

int     b_echo(char **input)
{
	int i;
	int flag;
	
	flag = TRUE;
	if (count_value(input) == 1)
		return (write(1, "\n", 1) - 1);
	i = echo_parameter(input);
	if (i > 1)
		flag = FALSE;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}