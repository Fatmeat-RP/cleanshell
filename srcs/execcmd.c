#include <minishell.h>

pid_t execmd1(t_exec *cmd, char **envp, int pipefd[2][2])//
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
//	if (cmd->prev->is_here_doc == true && last_cmd_pid)
//		waitpid(last_cmd_pid, &g_status, 0);
	if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
//		if (redirect1(cmd, pipefd) == 1)
//        	dup2(pipefd[0][1], STDOUT_FILENO);
		dup2(pipefd[1][0], STDIN_FILENO);
		close_pipe(pipefd);
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(g_status);
	}
	return(pid);
}

pid_t execmd2(t_exec *cmd, char **envp, int pipefd[2][2])//
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
//	if (cmd->prev->is_here_doc == true && last_cmd_pid)
//		waitpid(last_cmd_pid, &g_status, 0);
//   if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
//       execve(cmd->cmd[0], cmd->cmd, envp);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
//		if (redirect2(cmd, pipefd) == 1)
//        	dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close_pipe(pipefd);
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(g_status);
	}
	return (pid);
}

pid_t execmd_first(t_exec *cmd, char **envp, int pipefd[2][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
    if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
        execve(cmd->cmd[0], cmd->cmd, envp);
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

pid_t execmd_last_pair(t_exec *cmd, char **envp, int pipefd[2][2])//)//
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
//	if (cmd->prev->is_here_doc == true && last_cmd_pid)
//		waitpid(last_cmd_pid, &g_status, 0);
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
	    execve(cmd->cmd[0], cmd->cmd, envp);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
//		if (redirect1(cmd, pipefd) == 1)
//        	dup2(pipefd[0][0], STDIN_FILENO);
		close_pipe(pipefd);
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(g_status);
	}
	return (pid);
}

pid_t execmd_last_unpair(t_exec *cmd, char **envp, int pipefd[2][2])//)//
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
//	if (cmd->prev->is_here_doc == true && last_cmd_pid)
//		waitpid(last_cmd_pid, &g_status, 0);
//    if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
//        execve(cmd->cmd[0], cmd->cmd, envp);
	else if (pid == 0)
	{
		signal(SIGQUIT, sig_quit_handler);
		signal(SIGINT, sig_int_child_handler);
//		if (redirect2(cmd, pipefd) == 1)
//        	dup2(pipefd[1][0], STDIN_FILENO);
		close_pipe(pipefd);
		g_status = execve(cmd->cmd[0], cmd->cmd, envp);
		exit(g_status);
	}
	return (pid);
}
