/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:16:54 by makbas            #+#    #+#             */
/*   Updated: 2023/09/11 19:51:22 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dir(char *cmd)
{
	DIR	*dir;

	if (!cmd)
		exit(EXIT_SUCCESS);
	dir = opendir(cmd);
	if (dir && readdir(dir))
	{
		closedir(dir);
		printf("hata\n");
	}
}

char    *is_path_cmd(char *cmd)
{
    //char    *path;
    char    **paths;

    check_dir(cmd);
    if (!access(cmd, F_OK))
        return (NULL);
    paths = m_shell.paths;
    return (NULL);
    
}