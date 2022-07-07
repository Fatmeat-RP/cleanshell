/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:42:00 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/06 17:49:19 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_var	*set_var(char **envp)
{
	t_var	*var;
	t_var	*start;

	var = NULL;
	var = fill_var(var, envp);
	start = var;
	while (var)
	{
		var->start = start;
		var = var->next;
	}
	var = start;
	while (var)
	{
		printf("%s ==>%s\n", var->varname, var->value);
		var = var->next;
	}
	printf("\n\n");
	var = start;
	return (var);
}
