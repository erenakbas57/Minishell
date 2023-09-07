/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:10:43 by rdemiray          #+#    #+#             */
/*   Updated: 2023/09/07 19:11:47 by rdemiray         ###   ########.fr       */
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
	env->next = 0; //null
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