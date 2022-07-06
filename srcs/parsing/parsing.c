/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:09:27 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/23 16:04:31 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_control_parse	*parsing(char *line, char **envp)
{
	t_control_parse	*parsing;
	char			**line_tab;
	size_t			i;
	int				q;

	parsing = NULL;
	i = 0;
	q = 0;
	if (first_check(line))
	{
		line_tab = ft_split(line, '|', i, q);
		parsing = set_parseur(parsing, line_tab);
		if (!printer_error(parsing))
			return (NULL);
		cleaner(parsing);
	}
	return (parsing);
}
