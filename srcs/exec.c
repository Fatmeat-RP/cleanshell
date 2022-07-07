/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:21:49 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/10 15:50:08 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void close_pipe(int pipefd[2][2])
{
	close(pipefd[1][1]);
    close(pipefd[1][0]);
    close(pipefd[0][1]);
    close(pipefd[0][0]);
}

static int pipeur(int pipefd[2][2])
{
	if (pipe(pipefd[0]) == -1)
	    return (-1);
	if (pipe(pipefd[1]) == -1)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		return (-1);
	}
	return(0);
}

int	execution(t_control_parse *parse_list, t_instance *instance)
{
	t_control_exec	*exes;
    int             pipefd[2][2];
    pid_t	        pid;
    size_t          pipe_nb;

	pid = 0;
	if (pipeur(pipefd) == -1)
        return(-1);
	exes = structurize(parse_list, instance);
	if (exes->first->is_pipe == true)
	{
		pipe_nb = exec_size(exes);
		if (pipe_nb == 2)
			pid = twopipe(exes->iter, instance->envp, pipefd);
		if (pipe_nb == 3)
			pid = threepipe(exes->iter, instance->envp, pipefd);
		if (pipe_nb <= 4)
			pid = morepipe(exes, instance->envp, pipefd);
	}
	else
		pid = exec_one_cmd(exes->iter, instance->envp, pipefd);
	if (pid)
		waitpid(pid, &g_status, 0);
	return (0);
}
