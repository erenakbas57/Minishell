/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:55:40 by makbas            #+#    #+#             */
/*   Updated: 2023/09/19 16:43:19 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		perror("PWD");
	else if (g_mshell.process->execute[1])
		perror("PWD");
	else
		printf("%s\n", path);
	free(path);
	if (!is_parent() || g_mshell.process_count != 1)
		exit(errno);
	return (0);
}