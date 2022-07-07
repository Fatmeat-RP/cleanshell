#include <minishell.h>

pid_t	exec_one_cmd(t_exec *cmd, char **envp, int pipefd[2][2])
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
        redirect2(cmd, pipefd);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_pipe(pipefd);
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(g_status);
	}
	return (pid);
}

pid_t	twopipe(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = 0;
    pid = execmd_first(cmd, envp, pipefd);
	cmd = cmd->next;
    pid = execmd_last_pair(cmd, envp, pipefd, pid);
	return (pid);
}

pid_t	threepipe(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = 0;
    pid = execmd_first(cmd, envp, pipefd);
	cmd = cmd->next;
	pid = execmd2(cmd, envp, pipefd, pid);
	cmd = cmd->next;
    pid = execmd_last_unpair(cmd, envp, pipefd, pid);
	return (pid);
}

pid_t	morepipe(t_control_exec	*exes, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = 0;
    pid = execmd_first(exes->iter, envp, pipefd);
	while (exes->iter->next->next != NULL)
	{
		pid = execmd1(exes->iter, envp, pipefd, pid);
		exes->iter = exes->iter->next;
		if (exes->iter->next == NULL)
			break;
		pid = execmd2(exes->iter, envp, pipefd, pid);
		exes->iter = exes->iter->next;
	}
	if (exec_size(exes) % 2 == 0)
    	pid = execmd_last_pair(exes->iter, envp, pipefd, pid);
	else
		pid = execmd_last_unpair(exes->iter, envp, pipefd, pid);
	return (pid);
}