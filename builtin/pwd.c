/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:55:40 by makbas            #+#    #+#             */
/*   Updated: 2023/08/29 15:35:40 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     b_pwd()
{
  char *path;
  
  path = getcwd(NULL, 0);
  if (path == NULL)
    perror("PWD");
  else if (m_shell.process->execute[1])
    perror("PWD");
  else
    printf("%s\n", path);
  free(path);
  return 0;
}