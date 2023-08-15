/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 00:00:18 by makbas            #+#    #+#             */
/*   Updated: 2023/08/02 14:47:22 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_err(int type)
{
	char	*red;

	if (type == HERE_DOC)
		red = "<<";
	else if (type == RED_INPUT)
		red = "<";
	else if (type == RED_OUTPUT)
		red = ">";
	else if (type == RED_APPEND)
		red = ">>";
	else if (type == PIPE)
		red = "|";
	else
		red = "newline";
	errno = 258;
	write(2, "minishell: syntax error near unexpected token '", 47);
	write(2, red, ft_strlen(red));
	write(2, "'\n", 2);
}

char    **add_array(char **exe_red, char *token)
{
    char    **new_array;
    int     len;
    int     i;

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

int     append_process(t_token **token, t_process *process)
{
    char    *data;
    if ((*token)->type == STRING)
    {
        data = clear_quote((*token)->str);
        process->execute = add_array(process->execute, data);
        printf("%s\n", m_shell.process->execute[0]);
    }
    else
    {
        data = clear_quote((*token)->str);
        process->redirects = add_array(process->redirects, data);
        *token = (*token)->next;
        if (!(*token) || (*token)->type != STRING)
        {
            free_token();
            return (FALSE);
        }
        data = clear_quote((*token)->str);
        process->redirects = add_array(process->redirects, data);
    }
    return (TRUE);
}

void	free_token(void)
{
	t_token		*tmp;
	t_token		*token;

	token = m_shell.token;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = m_shell.token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}


void print_execute(t_process *process) {
    if (process == NULL || process->execute == NULL) {
        printf("No 'execute' data available.\n");
        return;
    }

    printf("Execute:\n");
    for (int i = 0; process->execute[i] != NULL; i++) {
        printf("%s\n", process->execute[i]);
    }
}

void print_redirects(t_process *process) {
    if (process == NULL || process->redirects == NULL) {
        printf("No 'redirects' data available.\n");
        return;
    }

    printf("Redirects:\n");
    for (int i = 0; process->redirects[i] != NULL; i++) {
        printf("%s\n", process->redirects[i]);
    }
}

int    lexerize()
{
    t_token     *token;
    t_process   *process;

    token = m_shell.token;
    while (token)
    {
        if (token->prev == NULL || token->type == PIPE)
        {
            if (token->type == PIPE)
                token = token->next;
            process = process_init();
            process_add_back(&m_shell.process, process);
        }
        if (!token)
            break;
        if (!append_process(&token, process))
            return (FALSE);
        if (token)
            token = token->next;
    }
    free_token();
    print_execute(m_shell.process);
    print_redirects(m_shell.process);
    return (TRUE);
}