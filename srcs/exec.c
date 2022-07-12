/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:21:49 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/09 00:51:43 by acarle-m         ###   ########.fr       */
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

int pipeur(int pipefd[2][2])
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

int	execution(t_control_exec *exes, t_instance *instance)
{
//    int             pipefd[2][2];
    pid_t	        pid;
//    size_t          pipe_nb;
//
	pid = 0;
/*	sleep(3);
	if (pipeur(pipefd) == -1)
        return(-1);
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
	else*/
	pid = exec_one_cmd(exes->iter, instance->envp);
	waitpid(pid, &g_status, 0);
	return (0);
}

pid_t	exec_one_cmd(t_exec *cmd, char **envp)
{
	pid_t	pid;

    if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
	{
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(g_status);
	}
	return (pid);
}
