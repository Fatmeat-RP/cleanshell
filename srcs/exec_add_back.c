/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:25:37 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/09 14:26:41 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_add_back(t_control_exec *lst, t_exec *add)
{
	if (lst->first == NULL)
		lst->first = add;
	else
	{
		lst->iter = exec_last(lst);
		add->prev = lst->iter;
		lst->iter->next = add;
		lst->iter = lst->first;
	}
	lst->size++;
}
