/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 00:00:18 by makbas            #+#    #+#             */
/*   Updated: 2023/09/18 17:54:57 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_array(char **exe_red, char *token)
{
	char	**new_array;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (exe_red && exe_red[len])
		len++;
	new_array = ft_calloc(sizeof(char *), len + 2);
	while (i < len)
	{
		new_array[i] = exe_red[i];
		i++;
	}
	new_array[i] = token;
	free(exe_red);
	return (new_array);
}

int	append_process(t_token **token, t_process *process)
{
	char	*data;

	if ((*token)->type == STRING)
	{
		data = clear_quote((*token)->str);
		process->execute = add_array(process->execute, data);
	}
	else
	{
		data = clear_quote((*token)->str);
		process->redirects = add_array(process->redirects, data);
		*token = (*token)->next;
		if (!(*token) || (*token)->type != STRING)
		{
			if (!(*token))
				token_error(0);
			else
				token_error((*token)->type);
			free_token();
			free_process();
			return (FALSE);
		}
		data = clear_quote((*token)->str);
		process->redirects = add_array(process->redirects, data);
	}
	return (TRUE);
}

int	lexerize(void)
{
	t_token		*token;
	t_process	*process;

	token = g_mshell.token;
	while (token)
	{
		if (token->prev == NULL || token->type == PIPE)
		{
			if (token->type == PIPE)
				token = token->next; // unexcepted token "|" hatası dönecek
			process = new_process();
			process_add_back(&g_mshell.process, process);
			g_mshell.process_count++;
		}
		if (!token)
			break ;
		if (!append_process(&token, process))
			return (FALSE);
		if (token)
			token = token->next;
	}
	free_token();
	return (TRUE);
}