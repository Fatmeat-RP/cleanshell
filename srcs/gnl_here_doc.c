/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:16:01 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/18 02:16:31 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_next_line(char **line)
{
	char	buffer[100];
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	while (i++ < 100)
		buffer[i] = 0;
	i = 0;
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0' && i < 100)
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	line[0] = buffer;
	return (r);
}