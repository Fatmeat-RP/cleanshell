/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:09:27 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:20:11 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing_printer(t_control_parse *parse_list)
{
	size_t	i;

	parse_list->iter = parse_list->first;
	i = 0;
	printf("INDEX\n");
	while (parse_list->iter)
	{
		printf("[%zu]->", i);
		parse_list->iter = parse_list->iter->next;
		i++;
	}
	parse_list->iter = parse_list->first;
	printf("\n\nELEM\n");
	while (parse_list->iter)
	{
		printf("[%s]->", parse_list->iter->elem);
		parse_list->iter = parse_list->iter->next;
	}
	parse_list->iter = parse_list->first;
	printf("\n\nFLAGS\n");
	while (parse_list->iter)
	{
		printf("[%d]->", parse_list->iter->flag);
		parse_list->iter = parse_list->iter->next;
	}
	printf("\n--------------------------------------");
	printf("\n\n");

//	print tempon
//	printf("\nelem a ajouter\n");
//	while (parse_list->iter)
//	{
//		printf("[%s]", parse_list->iter->flag);
//		parse_list->iter = parse_list->iter->next;
//	}

	return (0);
}

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
		line_tab = ft_split_it(line, '|', i, q);
		parsing = set_parseur(parsing, line_tab, envp);
		if (!printer_error(parsing))
		{
			cleaner(parsing);
			return (NULL);
		}
//		parsing_printer(parsing);
	}
	return (parsing);
}
