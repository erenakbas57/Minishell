/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:33:23 by makbas            #+#    #+#             */
/*   Updated: 2023/09/18 14:15:23 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_value(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	append_env(char **env)
{
	int		i;

	i = 0;
	g_mshell.envp = ft_calloc(sizeof(char **), 29);
	while (env[i])
	{
		env_add_back(&g_mshell.env, new_env(ft_strdup(env[i])));
		g_mshell.envp[i] = ft_strdup(env[i]);
		i++;
	}
}

void	append_export(void)
{
	t_env	*env;

	env = g_mshell.env;
	while (env)
	{
		export_add_back(&g_mshell.export, \
			new_export(ft_strjoin_two(env->str)));
		env = env->next;
	}
}

void	append_paths(void)
{
	char	*path;

	path = (g_mshell.env->next->next->str) + 5;
	g_mshell.paths = ft_split(path, ':');
}