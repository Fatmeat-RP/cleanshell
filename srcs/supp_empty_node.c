/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_empty_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:02:48 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	empty_elem(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (true);
	if (ft_strlen(s) == 0)
		return (true);
	return (false);
}

int	supp_empty_node(t_control_parse *parsing)
{
	size_t	i;
	t_parse	*tmp;
	int		ori_flag;

	i = 1;
	ori_flag = 0;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		tmp = parsing->first;
		if (empty_elem(parsing->first->elem))
		{
			parsing->first = parsing->first->next;
			parsing->iter = parsing->first;
			free(tmp->elem);
			free(tmp);
			tmp = NULL;
			ori_flag = 1;
		}
		else if (empty_elem(parsing->iter->elem))
		{
			while (tmp->next != parsing->iter)
				tmp = tmp->next;
			tmp->next = parsing->iter->next;
			free(parsing->iter->elem);
			free(parsing->iter);
			parsing->iter = tmp;
		}
		else
			parsing->iter = parsing->iter->next;
		i++;
	}
	return (ori_flag);
}
