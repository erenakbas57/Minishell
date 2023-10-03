/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:19:45 by rdemiray          #+#    #+#             */
/*   Updated: 2023/10/03 18:22:38 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_add(char *env)
{
	char	*path;
	t_env	*environment;
	char	*tmp;

	tmp = NULL;
	environment = g_mshell.env;
	env = ft_strjoin(env, "=");
	while (environment)
	{
		if (ft_strncmp(environment->str, env, ft_strlen(env)) == 0)
		{
			path = environment->str;
			while (*path != '=')
				path++;
			path++;
			free(env);
			return (path);
		}
		environment = environment->next;
	}
	if (env[0] == '?')
		tmp = ft_itoa(errno);
	else if (ft_strncmp(env, "0", 1) == 0)
		tmp = ft_strdup("bash");
	else
		tmp = ft_strdup("$");
	free(env);
	return (tmp);
}

void	env_control(char *token, char **str, int *token_i, int *str_i)
{
	char	*env;
	int		start;
	int		len;
	char	*tmp;
	int		i;

	start = *token_i;
	len = 0;
	while (!(ft_strchr(DOLLAR_CTRL, token[*token_i])))
	{
		(*token_i)++;
		len++;
	}
	env = ft_substr(token, start, len);
	tmp = env_add(env);
	free(env);
	if (tmp && tmp[0] == DOLLAR)
	{
		free(tmp);
		return ;
	}
	else
	{
		i = 0;
		while (tmp && tmp[i])
		{
			(*str)[*str_i] = tmp[i];
			(*str_i)++;
			i++;
		}
		if (tmp[0] == '0' || tmp[0] == 'b' || tmp[0] == '$')
			free(tmp);
		else if (tmp[0] >= '1' && tmp[0] <= '9')
			free(tmp);
	}
}

int	quote_control(char *quote)
{
	int	count;
	int	i;
	int	start;
	int	finish;

	start = 0;
	finish = 0;
	i = -1;
	count = 0;
	while (quote[i++] != DOLLAR)
	{
		if (quote[i] == SINGLE_QUOTE)
			start++;
	}
	while (quote[i++])
	{
		if (quote[i] == SINGLE_QUOTE)
			finish++;
	}
	count = start + finish;
	if (((count % 2 == 0) && (start % 2 == 1)) || \
		((finish == 1) && (start == 1)))
		return (0);
	if (count == 0)
		return (1);
	return (1);
}

char	*dollar_control(char *token)
{
	int		token_i;
	int		str_i;
	char	*str;
	int		i;

	str_i = 0;
	token_i = 0;
	if (ft_strchr(token, DOLLAR) && quote_control(token))
	{
		i = token_len(token);
		str = ft_calloc(sizeof(char), (i + 1));
		while (token[token_i])
		{
			if (token[token_i] == DOLLAR)
			{
				token_i++;
				env_control(token, &str, &token_i, &str_i);
			}
			else
			{
				str[str_i] = token[token_i];
				str_i++;
				token_i++;
			}
		}
		return (str);
	}
	token = ft_strdup(token);
	return (token);
}
