#include <minishell.h>

pid_t	forklift(t_exec *cmd, char **envp)
{
	int	pid;
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		redirect_in(cmd, pipefd);
		redirect_out(cmd, pipefd);
		exec_one_cmd(cmd, envp);
	}
	else
	{
		redirect_in(cmd->next, pipefd);
		waitpid(pid, &g_status, 0);
	}	
	return (pid);
}
