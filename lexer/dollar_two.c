/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:02:17 by makbas            #+#    #+#             */
/*   Updated: 2023/09/23 14:07:15 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(char *env)
{
	t_env	*environment;

	environment = g_mshell.env;
	env = ft_strjoin(env, "=");
	while (environment)
	{
		if (ft_strncmp(environment->str, env, ft_strlen(env)) == 0)
		{
			free(env);
			return ((int)(ft_strlen(environment->str) - ft_strlen(env)));
		}
		environment = environment->next;
	}
	free(env);
	return (0);
}

int	token_len(char *token)
{
	int		i;
	int		start;
	int		len;
	char	*env;

	i = 0;
	len = 0;
	start = 0;
	while (token[i])
	{
		if (token[i] == DOLLAR)
		{
			i++;
			start = i;
			while (!(ft_strchr(DOLLAR_CTRL, token[i])) && token[i])
				i++;
			env = ft_substr(token, start , i - start);
			len += env_len(env);
			free(env);
			start = 0;
			
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}