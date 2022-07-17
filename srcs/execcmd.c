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
	//	redirect_in(cmd, pipefd);
	//	redirect_out(cmd, pipefd);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_one_cmd(cmd, envp);
		
	}
	else
	{
		close(pipefd[1]);
		pipefd[0] = redirect_in(cmd->next, pipefd);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, &g_status, 0);
	}	
	return (pid);
}
