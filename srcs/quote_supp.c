/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_supp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 01:44:14 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:47:05 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cut_quote(t_parse *node, int nb_q)
{
	char	*new;
	size_t	i;
	size_t	j;
	int		q;

	i = 0;
	j = 0;
	q = 0;
	new = malloc(sizeof(char) * (ft_strlen(node->elem) - nb_q + 1));
	if (!new)
		return (0);
	while (node->elem[i])
	{
		if (q != tote(node->elem[i], q))
		{
			q = tote(node->elem[i], q);
			i++;
		}
		else
		{
			new[j] = node->elem[i];
			i++;
			j++;
		}
	}
	new[j] = '\0';
	free(node->elem);
	node->elem = new;
	return (1);
}

int	there_is_quote(char *s)
{
	size_t	i;
	int		q;
	int		nb_q;

	i = 0;
	q = 0;
	nb_q = 0;
	while (s[i])
	{
		if (q != tote(s[i], q))
		{
			q = tote(s[i], q);
			nb_q++;
		}
		i++;
	}
	return (nb_q);
}

int	quote_supp(t_control_parse *parsing)
{
	char	*s;
	int		nb_q;

	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		s = parsing->iter->elem;
		nb_q = there_is_quote(s);
		if (nb_q)
		{
			if (!cut_quote(parsing->iter, nb_q))
				return (0);
		}
		else
			parsing->iter = parsing->iter->next;
	}
	return (1);
}
