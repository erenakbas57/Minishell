/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdemiray <rdemiray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:57:01 by makbas            #+#    #+#             */
/*   Updated: 2023/09/07 19:10:05 by rdemiray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_add_back(t_export **export, t_export *new)
{
	t_export	*tmp_export;

	tmp_export = *export;
	if (!tmp_export)
		*export = new;
	else
	{
		while (tmp_export->next)
			tmp_export = tmp_export->next;
		tmp_export->next = new;
	}
}

t_export	*new_export(char *str)
{
	t_export	*export;

	export = ft_calloc(sizeof(t_export), 1);
	export->str = str;
	export->next = NULL;
	return (export);
}

t_export	*last_export(t_export *export)
{
	if (!export)
		return (0);
	while (export->next != 0)
		export = export->next;
	return (export);
}