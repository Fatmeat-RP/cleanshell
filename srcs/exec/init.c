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
	exe->is_pipe = false;
	exe->is_here_doc = false;
	exe->is_append = false;
	exe->next = NULL;
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

t_parse	*init_parse(char *elem, float flag)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	parse->elem = elem;
	parse->flag = flag;
	parse->next = NULL;
	return (parse);
}

t_control_parse	*init_control_parse(void)
{
	t_control_parse	*parse;

	parse = malloc(sizeof(t_control_parse));
	parse->first = NULL;
	parse->iter = NULL;
	parse->size = 0;
	return (parse);
}
