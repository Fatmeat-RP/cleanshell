/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:45:49 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_var	*fill_var(t_var *var, char **envp)
{
	size_t	i;
	t_var	*new;
	t_var	*first;
	
	i = 0;
	while (envp[i])
	{
		if (i == 0)
		{
			var = ft_lstnew(envp[i]);
			first = var;
			var = first;
		}
		else
		{
			new = ft_lstnew(envp[i]);
			var->next = new;
			var = new;
		}
		i++;
	}
	var->next = 0;
	dispatch_var(first);
	return (first);
}
