/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   universal_flaggeur.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:44:15 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/08 22:15:16 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	universal_flaggeur(t_control_parse *parsing)
{
	int	tem;

	tem = 0;
	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		if (parsing->iter->flag == ARGS_FLAG && tem == 0)
		{
			parsing->iter->flag = CMD_FLAG;
			tem = 1;
		}
		if (parsing->iter->flag == PIPE_FLAG)
			tem = 0;
		parsing->iter = parsing->iter->next;
	}
}
