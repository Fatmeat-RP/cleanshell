/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:42:39 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:42:57 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_parse	*parse(t_control_parse *parsing, size_t x, char **env)
{
	t_control_parse	*replace;

	replace = malloc(sizeof(t_control_parse));
	if (x > 1)
	{
		while (parsing->iter->next)
		{
			parse_add_just_back(parsing, init_parse(ft_strdup("|"), 7));
			parsing->iter = parsing->iter->next;
			parsing->iter = parsing->iter->next;
		}
	}
	if (x == 1)
		parsing->first->flag = 5;
	splitter(parsing, replace);
	dollar(replace, env);
	flaggeur_redir(replace);
	cut_redir(replace);
	flaggeur_redir(replace);
	flaggeur_file_name(replace);
	re_flaggeur(replace);
	check_multi_chev(replace);
	check_multi_node_chev(replace);
	check_no_file_name(replace);
	supp_empty_node(replace);
	quote_supp(replace);
	re_flaggeur(replace);
	cleaner(parsing);
	return (replace);
}
