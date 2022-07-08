/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multi_node_chev.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:36:27 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/08 22:15:16 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_node(t_parse *node)
{
	size_t	i;
	
	i = 0;
	free(node->elem);
	if (node->flag == REDIR_IN_FLAG
		|| node->flag == HERE_DOC_FLAG)
		node->elem = ft_strdup("syntax error near unexpected token `<'");
	if (node->flag == REDIR_OUT_FLAG
		|| node->flag == REDIR_OUT_ADD_FLAG)
		node->elem = ft_strdup("syntax error near unexpected token `>'");
	node->flag = PARSE_ERROR;
}

void	check_multi_node_chev(t_control_parse *parsing)
{
	t_control_parse	*cpy;

	cpy = malloc(sizeof(t_control_parse));
	parsing->iter = parsing->first;
	cpy->iter = parsing->iter->next;
	while (cpy->iter)
	{
		if (parsing->iter->flag == REDIR_IN_FLAG
			|| parsing->iter->flag == REDIR_OUT_FLAG
			|| parsing->iter->flag == HERE_DOC_FLAG
			|| parsing->iter->flag == REDIR_OUT_ADD_FLAG)
		{
			if (cpy->iter->flag == REDIR_IN_FLAG
				|| cpy->iter->flag == REDIR_OUT_FLAG
				|| cpy->iter->flag == HERE_DOC_FLAG
				|| cpy->iter->flag == REDIR_OUT_ADD_FLAG)
			{
				replace_node(parsing->iter->next);
				break ;
			}
		}
			cpy->iter = cpy->iter->next;
			parsing->iter = parsing->iter->next;
	}
	free(cpy);
}
