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

pid_t execmd1(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
//        redirect(cmd, envp, pipefd);
        dup2(pipefd[0][1], STDOUT_FILENO);
		dup2(pipefd[1][0], STDIN_FILENO);
		close_pipe(pipefd);
		status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(status);
	}
	return(pid);
}

pid_t execmd2(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
//        redirect(cmd, envp, pipefd);
        dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_pipe(pipefd);
		status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(status);
	}
	return (pid);
}

int	execution(t_control_parse *parse_list, t_instance *instance)
{
	t_control_exec	*exes;
    int             pipefd[2][2];
    pid_t	        pid;

    status = 0;
    if (pipe(pipefd[0]) == -1)
        return (-1);
	if (pipe(pipefd[1]) == -1)
	{
		close(pipefd[0][0]);
		close(pipefd[0][1]);
		return (-1);
	}
	exes = structurize(parse_list);
	while (exes->iter->next->next != NULL)
	{
        if (ft_strncmp(exes->iter->cmd[0], "cd", 3) == 0)
            execve(exes->iter->cmd[0], exes->iter->cmd, instance->envp);
		pid = execmd1(exes->iter, instance->envp, pipefd);
		exes->iter = exes->iter->next;
        replace_status(exes->iter);
		pid = execmd2(exes->iter, instance->envp, pipefd);
		exes->iter = exes->iter->next;
        replace_status(exes->iter);
	}
	waitpid(pid, &instance->status, 0);
	return (0);
}
