/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:42:36 by rdemiray          #+#    #+#             */
/*   Updated: 2023/09/19 16:45:05 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//dup2 function
//dup2(oldfd, 0) 0 burda input olarak standart giriş kullanılmasını sağlar.


void inputs(char *file_name)
{
	int fd;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return(nofile_error(file_name));
	dup2(fd, 0);
	close(fd);
}

//O_TRUNC dosya varsa ve normal bir dosyaysa uzunluğu sıfırlanır ve değiştimeye açılır. dosyayı yeniler yani
//O_APPEND dosyanın sonuna yazmaya devam eder diye yorumladım.
void outputs(char *file_name, int mode)
{
	int fd;
	fd = 0;
	if(mode == 1)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if(mode == 0)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("minishell");
		if (is_parent())
			return ;
		else
			exit(errno);
	}
	dup2(fd, 1);
	close(fd);
}

void get_inputs(t_process *process)
{
	int i;
	i = 0;
	char **redirect;
	redirect = process->redirects;
	while(redirect[i])
	{
		if(is_redirects(redirect[i]) == HERE_DOC)
			dup2(process->heredoc_fd[0], 0);
		else if(is_redirects(redirect[i]) == RED_INPUT)
			inputs(redirect[i + 1]);
		i = i+ 2;
	}
}

void	set_outputs(t_process *process)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_redirects(redirects[i]) == RED_OUTPUT)
			outputs(redirects[i+1], 1);      //output 1 replace et, > gelirse dosyayı yeniden oluşturur.
		else if (is_redirects(redirects[i]) == RED_APPEND)
			outputs(redirects[i+1], 0);  //output 0, 0 means append et >> gelirse bir dosyanın sonuna yazmaya devam edicek 
		i = i + 2;
	}
}
