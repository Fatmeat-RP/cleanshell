/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:20:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/04/27 17:28:44 by cben-bar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int g_status;

int main(int ac, char **av, char **envp)
{
	t_instance	*instance;

	(void)ac;
	(void)av;
	g_status = 0;
	instance = init_minishell(envp);
	while (1)
	{
		instance->line = readline(instance->prompt);
		if (!instance->line)
		{
			rl_clear_history();
			return (-1);
		}
		else if (instance->line[0] != 0)
			instance = if_line(instance);
	}
	rl_clear_history();
	return (0);
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

t_instance *if_line(t_instance *instance)
{
	t_control_parse	*parse_list;

	add_history(instance->line);
//	parse_list = parsing(instance->line, instance->envp);
	sleep(1);
	g_status = -1;
	return(instance);
	//if (!parse_list)
	//{
	//    instance->status = -1;
	//    return(instance);
	//}
	printf("caca");
	execution(parse_list, instance);
	return_prompt(instance);
	return (instance);
}
