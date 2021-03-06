/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_parseur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:24:14 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_parse	*set_parseur(t_control_parse *parsing, char **line_tab, char **env)
{
	size_t	i;
	size_t	x;

	i = 0;
	x = 0;
	parsing = init_control_parse();
	while (line_tab[i])
	{
		parse_add_back(parsing, init_parse(ft_strdup(line_tab[i]), 0));
		i++;
	}
	while (line_tab[x])
		x++;
	tab_cleaner(line_tab);
	parsing = parse(parsing, x, env);
	return (parsing);
}
