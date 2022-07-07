/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:42:39 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/06 17:44:04 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_parse	*parse(t_control_parse *parsing, size_t x, char **env)
{
	(void)env;
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
	splitter(parsing, replace);
	dollar(replace, env);
	flaggeur_redir(replace);
	cut_redir(replace);
	flaggeur_redir(replace);
	flaggeur_file_name(replace);
	universal_flaggeur(replace);
	check_multi_chev(replace);
	check_multi_node_chev(replace);
	check_no_file_name(replace);
	quote_supp(replace);
	cleaner(parsing);
	return (replace);
}
