/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:20:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/09 00:51:41 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_status;

int main(int ac, char **av, char **envp)
{
	t_instance	*instance;

	(void)ac;
	(void)av;
	instance = init_minishell(envp);
	if (!instance)
		return (-1);
	while (1)
	{
		instance->line = readline(instance->prompt);
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

t_instance *init_minishell(char **envp)
{
	t_instance	*instance;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
	instance = malloc(sizeof(t_instance *));
	if (!instance)
		return (NULL);
	instance->envp = envp;
	instance->prompt = malloc(25);
	if (!instance->prompt)
	{
		free(instance);
		return (NULL);
	}
	strcpy(instance->prompt, "\033[33;1mminishell $> \033[0m");
	return (instance);
}

void	if_line(t_instance *instance)
{
	t_control_parse	*parse;
	t_control_exec	*exec;
	int				nb_pipe;

	nb_pipe = 0;
	add_history(instance->line);
	parse = parsing(instance->line, instance->envp);
	if (control_parse(parse) == -1)
	    return (return_prompt(instance));
	parse->iter = parse->first;
	nb_pipe = pipe_counter(parse);
	exec = struct2(parse, nb_pipe, instance->envp);
	parse->iter = parse->first;
	if (!exec)
	{
		cleaner(parse);
	    return(return_prompt(instance));
	}
	execution(exec, instance);
	cleaner(parse);
	exec_cleaner(exec);
	return (return_prompt(instance));
}
