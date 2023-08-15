/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:58:55 by makbas            #+#    #+#             */
/*   Updated: 2023/07/23 15:05:12 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*source;

	i = 0;
	source = (unsigned char *)b;
	while (i < len)
	{
		source[i] = c;
		i++;
	}
	return (b = source);
}