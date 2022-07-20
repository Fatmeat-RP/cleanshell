/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:20:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/18 02:48:52 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_status;

int main(int ac, char **av, char **envp)
{
	t_instance	*instance;

	instance = init_minishell(envp, ac, av);
	if (!instance)
		return (-1);
	while (1)
	{
		instance->line = readline("minishell $>");
		if (!instance->line)
		{
			rl_clear_history();
			return (free_instance(instance, -1));
		}
		else if (instance->line[0] != 0)
		{
			if (ft_strncmp(instance->line, "exit", 5) == 0)
				return (free_instance(instance, -1));
			if_line(instance);
		}
	}
	rl_clear_history();
	return (free_instance(instance, 0));
}

t_instance *init_minishell(char **envp, int ac, char **av)
{
	t_instance	*instance;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
	instance = malloc(sizeof(t_instance *));
	if (!instance)
		return (NULL);
	instance->builtin = init_builtin();
	instance->envp = envp;
	return (instance);
}

int	if_line(t_instance *instance)
{
	t_control_parse	*parse;
	t_control_exec	*exec;
	int				nb_pipe;

	nb_pipe = 0;
	add_history(instance->line);
	parse = parsing(instance->line, instance->envp);
	if (control_parse(parse) == -1)
	    return (-1);
	parse->iter = parse->first;
	nb_pipe = pipe_counter(parse);
	exec = struct2(parse, nb_pipe, instance->envp);
	parse->iter = parse->first;
	if (!exec)
	{
		cleaner(parse);
	    return(-1);
	}
	execution(exec, instance);
	cleaner(parse);
	exec_cleaner(exec);
	return (0);
}
