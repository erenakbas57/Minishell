/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 15:14:22 by makbas            #+#    #+#             */
/*   Updated: 2023/09/22 18:56:14 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(char *env)
{
	t_env	*environment;

	environment = g_mshell.env;
	env = ft_strjoin(env, "=");
	//printf("1env : %p\n", env);
	while (environment)
	{
		if (ft_strncmp(environment->str, env, ft_strlen(env)) == 0)
		{
			free(env);
			//printf("env uzunluk : %d\n\n", (int)(ft_strlen(environment->str) - ft_strlen(env)));
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
			while (!(ft_strchr(">£#$½§{[|]}*-~,;.:!'^+&/{}\"\'%% ", token[i])) && token[i])
				i++;
			//printf("token[i] ve start : %d - %c ve %d - %c\n", i, token[i], start, token[start]);
			env = ft_substr(token, start , i - start);
			//printf("2env : %p ve str'si :-- %s\n", &env, env);
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

char	*env_add(char* env)
{
	char	*path;
	t_env	*environment;
	char	*str;

	environment = g_mshell.env;
	env = ft_strjoin(env, "=");
	while (environment)
	{
		if (ft_strncmp(environment->str, env, ft_strlen(env)) == 0)
		{
			path = environment->str;
			str = ft_substr(path, ft_strlen(env), \
				ft_strlen(path) - ft_strlen(env));
			free(env);
			return (str);
		}
		environment = environment->next;
	}
	free(env);
	env = ft_strdup("");
	return (env);
}


void env_control(char *token, char **str, int *i)
{
	int		len;
	int		start;
	char	*env;
	char	*cpy;

	len = 0;
	start = *i;
	while (token[*i] && is_char(token[*i]))
	{
		(*i)++;
		len++;
	}
	env = ft_substr(token, start, len);
	len = ft_strlen(env) + 1;
	cpy = env_add(env);
	free(env);
	if (cpy[0] != DOLLAR)
		*str = ft_strjoin(*str, cpy);
	// else if (cpy[0] == '\0')
	// 	*str = ft_strjoin(*str, "");
	free(cpy);
}

int quote_control(char *quote)
{
	int count;
	int i;
	int start;
	int finish;
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

char    *dollar_control(char *token)
{
	int     token_i;
	int     str_i;
	char    *str;
	int		i;

	str_i = 0;
	token_i = 0;
	if (ft_strchr(token, DOLLAR) && quote_control(token))
	{
		i = token_len(token);
		str = ft_calloc(sizeof(char),  ( i + 1));
		while (token[token_i])
		{
			if (token[token_i] == DOLLAR)
			{
				token_i++;
				env_control(token, &str, &token_i);
				str_i = ft_strlen(str);
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