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

int	execution(t_control_exec *exes, t_instance *instance)
{
	int		old_in;
	int		old_out;
	pid_t	pid;

	old_in = dup(STDIN_FILENO);
	old_out = dup(STDOUT_FILENO);
	while (exes->iter->next != NULL)
	{
		forklift(exes->iter, instance->envp);
		exes->iter = exes->iter->next;
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec_one_cmd(exes->iter, instance->envp);
	waitpid(pid, &g_status, 0);
	dup2(old_out, STDOUT_FILENO);
	dup2(old_in, STDIN_FILENO);
	close(old_in);
	close(old_out);
	return (0);
}

void	exec_one_cmd(t_exec *cmd, char **envp)
{
//	redirect_out(cmd);
	signal(SIGQUIT, sig_quit_handler);
	signal(SIGINT, sig_int_child_handler);
	g_status = execve(cmd->cmd[0], cmd->cmd, envp);
	exit(g_status);
}
