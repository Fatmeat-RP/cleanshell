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
//		redirect_out(cmd, pipefd);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_one_cmd(cmd, envp);
	}
	else
	{
//		redirect_out(cmd, pipefd);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		write(0, "\r", 1);
		waitpid(pid, &g_status, 0);
	}	
	return (pid);
}
