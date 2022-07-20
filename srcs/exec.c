/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:21:49 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/18 02:24:54 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	chose_exec(t_control_exec *exes, t_instance *instance)
{
	if (exes->first->next == NULL)
		return (execution_solo());
	else
		return (execution_pipe());
}

int	execution_solo(t_control_exec *exes, t_instance *instance)
{
	pid_t	pid;
	int		pipefd[2];
 
	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_one_cmd(exes->iter, instance->envp);
	else
		waitpid(pid, &g_status, 0);
}

int	execution_pipe(t_control_exec *exes, t_instance *instance)
{
}

int	execution(t_control_exec *exes, t_instance *instance)
{
	int		old_in;
	pid_t	pid;
	int		fdin;

	old_in = dup(STDIN_FILENO);
	while (exes->iter->next != NULL)
	{
		fdin = forklift(exes->iter, instance->envp, fdin);
		exes->iter = exes->iter->next;
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_one_cmd(exes->iter, instance->envp);
	waitpid(pid, &g_status, 0);
	dup2(old_in, STDIN_FILENO);
	close(old_in);
	return (0);
}

void	exec_one_cmd(t_exec *cmd, char **envp)
{
	int	fd[1];

	signal(SIGINT, sig_int_child_handler);
	signal(SIGQUIT, sig_quit_handler);
	fd[0] = 0;
	fd[1] = 1;
	here_doc(cmd, fd);
	fd[0] = redirect_in(cmd, fd);
	if (fd[0] == -1 && cmd->in[0] != NULL)
	{
		write(1, "minishell: ", 12);
		write(1, cmd->in[line_counter(cmd->in)],
			ft_strlen(cmd->in[line_counter(cmd->in)]));
		write(1, ": No such file or directory\n", 29);
		g_status = 1;
		exit (g_status);
	}
	fd[1] = redirect_out(cmd, fd);
	if (fd[0])
		dup2(fd[0], STDIN_FILENO);
	if (fd[1])
		dup2(fd[1], STDOUT_FILENO);
	g_status = execve(cmd->cmd[0], cmd->cmd, envp);
	close(fd[0]);
	close(fd[1]);
	exit(g_status);
}
