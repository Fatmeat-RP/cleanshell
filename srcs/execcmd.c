#include <minishell.h>

int	forklift(t_exec *cmd, char **envp, int fdin)
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
	//	pipefd = redirect_in_pipe(cmd, pipefd);
		here_doc(cmd, pipefd);
		redirect_out(cmd, pipefd);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_one_cmd(cmd, envp);
	}
	else
	{
		close(fdin);
		close(pipefd[1]);
		pipefd[0] = redirect_in(cmd->next, pipefd);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, &g_status, 0);
	}	
	return (pipefd[0]);
}

int	exec_cmd_pipe(t_exec *cmd, t_builtin *builtin)
{
	if (cmd->is_builtin == true)
	{
		while(builtin->iter->next && ft_strcmp(cmd->cmd[0], builtin[->name) != 0)
			builtin->iter = builtin->iter->next;
		exit(*builtin->fun)(cmd->cmd);
	}
	else
	{

	}
}