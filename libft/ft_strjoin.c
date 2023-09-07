/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:09:31 by makbas            #+#    #+#             */
/*   Updated: 2023/09/07 15:52:12 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s;
	char	*join;

	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	s = 0;
	if (!join)
		return (0);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[s] != '\0')
	{
		join[i] = s2[s];
		s++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

void	add_declare(char **join)
{
	int		i;
	char	*dec;

	dec = ft_calloc(sizeof(char), 11);
	dec = "declare -x ";
	i = 0;
	while (dec[i])
	{
		(*join)[i] = dec[i];
		i++;
	}
}

char	*ft_strjoin_two(char const *s1)
{
	int		i;
	int		j;
	char	*join;
	
	join = ft_calloc((ft_strlen(s1) + 14), 1);
	i = 0;
	j = 11;
	if (!join)
		return (0);
	add_declare(&join);
	printf("-%s-\n", join);
	while (s1[i] != '\0')
	{
		if (s1[i] == '=')
		{
			join[j] = s1[i];
			j++;
			join[j] = '\"';
		}
		else
			join[j] = s1[i];
		i++;
		j++;
	}
	join[j] = '\"';
	return (join);
}