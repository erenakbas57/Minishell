/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:06:24 by makbas            #+#    #+#             */
/*   Updated: 2023/09/19 16:42:52 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_write(char *str)
{
	int		i;
	char	*path;
	t_env	*env;

	i = 0;
	str = ft_strjoin(str, "=");
	env = g_mshell.env;
	while (env)
	{
		if (ft_strncmp(env->str, str, ft_strlen(str)) == 0)
		{
			path = env->str;
			str = ft_substr(path, ft_strlen(str), \
				ft_strlen(path) - ft_strlen(str));
			printf("%s\n", str);
			return ;
		}
		env = env->next;
	}
	printf("ENV: ");
	printf("%s: ", g_mshell.process->execute[1]);
	printf("No such file or directory\n");
}

int	b_env(void)
{
	t_env	*env;
	char	**exe;

	env = g_mshell.env;
	exe = g_mshell.process->execute;
	if (exe[1] == NULL)
	{
		while (env)
		{
			printf("%s\n", env->str);
			env = env->next;
		}
	}
	else if (exe[1] != NULL && exe[2] == NULL)
	{
		env_write(exe[1]);
	}
	else
	{
		printf("usage: ");
		printf("pwd [-L | -P]: \n");
	}
	if (!is_parent())
		exit (EXIT_SUCCESS);
	return (0);
}