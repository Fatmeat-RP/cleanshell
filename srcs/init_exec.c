/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:18:59 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/09 14:25:54 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_exec	*init_exe(void)
{
	t_exec	*exe;

	exe = (t_exec *)malloc(sizeof(t_exec));
	exe->cmd = NULL;
	exe->in = NULL;
	exe->out = NULL;
	exe->limiter = NULL;
	exe->is_pipe = false;
	exe->is_here_doc = false;
	exe->is_append = NULL;
	exe->next = NULL;
	exe->prev = NULL;
	return (exe);
}

t_control_exec	*init_exe_list(void)
{
	t_control_exec	*exe;

	exe = (t_control_exec *)malloc(sizeof(t_control_exec));
	exe->first = NULL;
	exe->iter = NULL;
	exe->size = 0;
	return (exe);
}
