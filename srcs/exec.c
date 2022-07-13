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
    pid_t	pid;
	int		old_in;
	int		old_out;

	pid = 0;
	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);
	while (exes->iter->next != NULL)
	{
		forklift(exes->iter, instance->envp);
		exes->iter = exes->iter->next;
	}
	dup2(old_out, STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		exec_one_cmd(exes->iter, instance->envp);
	}
	waitpid(pid, &g_status, 0);
	dup2(old_in, STDIN_FILENO);
	close(old_in);
	return (0);
}

void	exec_one_cmd(t_exec *cmd, char **envp)
{
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_child_handler);
	g_status = execve(cmd->cmd[0], cmd->cmd, envp);
	exit(g_status);
}
