/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 23:12:11 by makbas            #+#    #+#             */
/*   Updated: 2023/09/11 19:10:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (FALSE);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (FALSE);
		s1++;
		s2++;
	}
	return (TRUE);
}


int	ft_strcmp_ex(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (FALSE);
	s1 += 11;
	while (!(*s2 == '=' || *s1 == '=') && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return (FALSE);
		s1++;
		s2++;
	}
	return (TRUE);
}

int	ft_strcmp_env(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (FALSE);
	while (!(*s2 == '=') && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return (FALSE);
		s1++;
		s2++;
	}
	return (TRUE);
}