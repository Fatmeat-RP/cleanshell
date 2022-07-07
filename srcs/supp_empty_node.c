/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_empty_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:02:48 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/07 15:58:37 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	empty_elem(char *s)
{
	if (!s)
		return (true);
	if (ft_strlen(s) == 0)
		return (true);
	return (false);
}

void	supp_empty_node(t_control_parse *parsing)
{
	size_t			i;
	t_parse			*node_prev;
	t_parse	*tmp;

	i = 1;
	node_prev = NULL;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (empty_elem(parsing->first->elem))
		{
			tmp = parsing->first;
			parsing->first = parsing->first->next;
			free(tmp->elem);
			free(tmp);
			tmp = NULL;
		}
		else if (empty_elem(parsing->iter->elem))
		{
			if (parsing->iter->next)
			{
				node_prev->next = parsing->iter->next;
				free(parsing->iter->elem);
				free(parsing->iter);
			}
			else
			{
				node_prev->next = NULL;
				free(parsing->iter->elem);
				free(parsing->iter);
			}
		}
		node_prev = parsing->iter;
		parsing->iter = parsing->iter->next;
		i++;
	}
//checker deux noeud vides a la suite (quid du next?)
}
