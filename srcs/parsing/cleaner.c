/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:26:54 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/07 18:14:40 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleaner(t_control_parse *parsing)
{
	t_parse	*ptr;

	while (parsing->first)
	{
		ptr = parsing->first;
		free(ptr->elem);
		parsing->first = parsing->first->next;
		free(ptr);
	}
	free(parsing);
}

void	tab_cleaner(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
