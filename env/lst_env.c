/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:53:58 by makbas            #+#    #+#             */
/*   Updated: 2023/09/07 17:54:22 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp_env;

	tmp_env = *env;
	if (!tmp_env)
		*env = new;
	else
	{
		while (tmp_env->next)
			tmp_env = tmp_env->next;
		tmp_env->next = new;
	}
}

t_env	*new_env(char *str)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	env->str = str;
	env->next = NULL;
	return (env);
}

t_env	*last_env(t_env *env)
{
	if (!env)
		return (0);
	while (env->next != 0)
		env = env->next;
	return (env);
}