#include <minishell.h>

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
        redirect1(cmd, envp, pipefd);
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
    if (ft_strncmp(exes->iter->cmd[0], "cd", 3) == 0)
        execve(exes->iter->cmd[0], exes->iter->cmd, instance->envp);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
        redirect2(cmd, envp, pipefd);
        dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_pipe(pipefd);
		status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(status);
	}
	return (pid);
}

pid_t execmd_first(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
    if (ft_strncmp(exes->iter->cmd[0], "cd", 3) == 0)
        execve(exes->iter->cmd[0], exes->iter->cmd, instance->envp);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
        redirect2(cmd, envp, pipefd);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_pipe(pipefd);
		status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(status);
	}
	return (pid);
}

pid_t execmd_last(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
    if (ft_strncmp(exes->iter->cmd[0], "cd", 3) == 0)
        execve(exes->iter->cmd[0], exes->iter->cmd, instance->envp);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
        redirect2(cmd, envp, pipefd);
        dup2(pipefd[0][0], STDIN_FILENO);
		close_pipe(pipefd);
		status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(status);
	}
	return (pid);
}
