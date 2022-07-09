/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_flaggeur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 00:11:53 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	re_flaggeur(t_control_parse *parsing)
{
	int				tem_flag;
	t_parse			*tmp;

	parsing->iter = parsing->first;
	while (parsing->iter)
	{
		tem_flag = 0;
		tmp = parsing->iter;
		while (parsing->iter && parsing->iter->flag != PIPE_FLAG)
		{
			if (parsing->iter->flag == CMD_FLAG) //PENSER AUX BUILTINS
				tem_flag = 1;
			parsing->iter = parsing->iter->next;	
		}
		if (tem_flag == 0)
		{
			while (tmp && tmp != parsing->iter)
			{
				if (tmp->flag == ARGS_FLAG)
				{
					tmp->flag = CMD_FLAG;
					break ;
				}
				tmp = tmp->next;
			}
		}
		if (parsing->iter)
			parsing->iter = parsing->iter->next;
	}
}	
