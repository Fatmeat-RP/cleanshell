/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:36:44 by cben-bar          #+#    #+#             */
/*   Updated: 2022/05/27 20:30:08 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	check_empty_line(char *line)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(line))
	{
		return (false);
	}
	else
	{
		while (line[i] == ' ')
		{
			if (line[i + 1] == '\0')
			{
				return (false);
			}
			i++;
		}
	}
	return (true);
}
