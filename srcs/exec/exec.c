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

static void close_pipe(int pipefd[2][2])
{
	close(pipefd[1][1]);
    close(pipefd[1][0]);
    close(pipefd[0][1]);
    close(pipefd[0][0]);
}

static int pipeur(int *pipefd[2][2])
{
    if (pipe(pipefd[0]) == -1)
        return (-1);
	if (pipe(pipefd[1]) == -1)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		return (-1);
	}
}

int	execution(t_control_parse *parse_list, t_instance *instance)
{
	t_control_exec	*exes;
    int             pipefd[2][2];
    pid_t	        pid;
    size_t          pipe_nb;

    status = 0;
    if (pipeur(&pipefd) == -1)
        return(-1);
	exes = structurize(parse_list);
	if (exes->first->is_pipe = true)
	{
		pipe_nb = exec_size(exes->iter);
		if (pipe_nb == 2)
			pid = twopipe();
		if (pipe_nb == 3)
			pid = threepipe();
		if (pipe_nb <= 4)
			pid = morepipe();
	}
	else
		pid = exec_one_cmd();
	waitpid(pid, &g_status, 0);
	return (0);
}

pid_t	twopipe(t_exec *cmd, char **envp, int pipefd[2][2])
{
    pid = execmd_first(exes->iter, instance->envp, pipefd);
	exes->iter = exes->iter->next;
	pid = execmd1(exes->iter, instance->envp, pipefd);
	exes->iter = exes->iter->next;
    pid = execmd_last(exes->iter, instance->envp, pipefd);
	return (pid)
}

pid_t	threepipe(t_exec *cmd, char **envp, int pipefd[2][2])
{
    pid = execmd_first(exes->iter, instance->envp, pipefd);
		pid = execmd2(exes->iter, instance->envp, pipefd);
		exes->iter = exes->iter->next;
    pid = execmd_last(exes->iter, instance->envp, pipefd);
	return (pid)
}

pid_t	morepipe(t_exec *cmd, char **envp, int pipefd[2][2])
{
    pid = execmd_first(exes->iter, instance->envp, pipefd);
	while (exes->iter->next->next != NULL)
	{
		pid = execmd1(exes->iter, instance->envp, pipefd);
		exes->iter = exes->iter->next;
		if (exes->iter->next == NULL)
			break;
		pid = execmd2(exes->iter, instance->envp, pipefd);
		exes->iter = exes->iter->next;
	}
	if (exec_size(exes->first) % 2 == 0)
    	pid = execmd_last_pair(exes->iter, instance->envp, pipefd);
	else
		pid = execmd_last_unpair(exes->iter, instance->envp, pipefd);
	return (pid)
}
