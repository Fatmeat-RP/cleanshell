/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:54:57 by cben-bar          #+#    #+#             */
/*   Updated: 2022/06/23 22:01:39 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	var_clear(t_var **var)
{
	t_var	*tmp;

	if (*var)
	{
		while (*var)
		{
			tmp = (*var)->next;
			free((*var)->varname);
			free((*var)->value);
			free(var);
			*var = tmp;
		}
		*var = NULL;
	}
}
