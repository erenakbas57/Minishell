/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:44:59 by makbas            #+#    #+#             */
/*   Updated: 2023/09/02 17:25:33 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	char	*d;
	int		i;

	i = 0;
	d = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (d == NULL)
		return (0);
	while (str[i])
	{
		d[i] = str[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strdup_two(const char *str)
{
	char	*d;
	int		i;

	i = 0;
	d = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (d == NULL)
		return (0);
	while (str[i])
	{
		d[i] = str[i];
		i++;
	}
	d[i++] = '\"';
	d[i++] = '\"';
	d[i] = '\0';
	return (d);
}