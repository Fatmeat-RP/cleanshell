/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multi_chev.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:30:46 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_error_chev(t_parse *node, char c)
{
	if (c == '<')
	{
		node->flag = PARSE_ERROR;
		free(node->elem);
		node->elem = ft_strdup("syntax error near unexpected token `<'\n");
	}
	if (c == '>')
	{
		node->flag = PARSE_ERROR;
		free(node->elem);
		node->elem = ft_strdup("syntax error near unexpected token `>'\n");
	}
}

void	check_multi_chev(t_control_parse *parsing)
{
	char	*s;

	parsing->iter = parsing->first;
	while (parsing->iter->next)
	{
		s = parsing->iter->elem;
		if ((parsing->iter->flag == HERE_DOC_FLAG) && (ft_strlen(s) > 2))
			parse_error_chev(parsing->iter, '<');
		else if ((parsing->iter->flag == REDIR_IN_FLAG)
			&& (ft_strlen(s) > 1))
			parse_error_chev(parsing->iter, '<');
		else if ((parsing->iter->flag == REDIR_OUT_ADD_FLAG)
			&& (ft_strlen(s) > 2))
			parse_error_chev(parsing->iter, '>');
		else if ((parsing->iter->flag == REDIR_OUT_FLAG)
			&& (ft_strlen(s) > 1))
			parse_error_chev(parsing->iter, '>');
		parsing->iter = parsing->iter->next;
	}
}
