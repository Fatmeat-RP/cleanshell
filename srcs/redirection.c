/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:02:45 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/10 16:15:40 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int redirect_in(t_exec *cmd, int pipefd[2])
{
	int i;
	char *line;

	i = 0;
	while (cmd->in[i + 1] != NULL)
		i++;
	if (i > 0)
	{
		close(pipefd[0]);
		pipefd[0] = open(cmd->in[i], O_RDONLY);
	}
	if (cmd->is_here_doc == true)
	{
		while (ft_strncmp(line, cmd->limiter, ft_strlen(cmd->limiter)) != 0)
			get_next_line(&line);
		return (1);
	}
	return (0);
}

int redirect_out(t_exec *cmd, int pipefd[2])
{
	int	i;

	i = 0;
	while (cmd->out[i] != NULL)
	{
		close(pipefd[0]);
		if (cmd->is_append[i] == '0')
			pipefd[0] = open(cmd->out[i], O_CREAT | O_APPEND | O_WRONLY);
		else
			pipefd[0] = open(cmd->out[i], O_CREAT | O_WRONLY);
		i++;
	}
	return (0);
}

/*int redirect_onecmd(t_exec *cmd)
{
	int	i;
//	int fd[2];
	char *line;

	i = 0;
	while (cmd->in[i + 1] != NULL)
		i++;
	if (i > 0)
	{
//		close(fd[0]);
		fd[0] = open(cmd->in[i], O_RDONLY);
		dup2(fd[0], STDIN_FILENO);
	}
	if (cmd->is_here_doc == true)
	{
		while (ft_strncmp(line, cmd->limiter, ft_strlen(cmd->limiter)) != 0)
			get_next_line(&line);
		return (1);
	}
	i = 0;
	while (cmd->out[i] != NULL)
	{
		close(fd[1]);
		if (cmd->is_append[i] == '0')
			fd[1] = open(cmd->out[i], O_CREAT | O_APPEND | O_WRONLY);
		else
			fd[1] = open(cmd->out[i], O_CREAT | O_WRONLY);
		i++;
	}
	if (i > 0)
		dup2(fd[1], STDOUT_FILENO);
	return (0);
}*/
