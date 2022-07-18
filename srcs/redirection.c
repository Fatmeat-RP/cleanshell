/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:02:45 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/18 02:17:36 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int redirect_in(t_exec *cmd, int pipefd[2])
{
	int i;
//	char *line;

	i = 0;
	while (cmd->in[i + 1] != NULL)
		i++;
	if (cmd->in[0] != NULL)
	{
		if (access(cmd->in[i], F_OK | R_OK) == -1)
			return (-1);
		close(pipefd[0]);
		pipefd[0] = open(cmd->in[i], O_RDONLY);
		if (pipefd[0] == -1)
			return (-1);
	}
	return (pipefd[0]);
}

int redirect_out(t_exec *cmd, int pipefd[2])
{
	int	i;

	i = 0;
	while (cmd->out[i] != NULL)
	{
		close(pipefd[1]);
		if (cmd->is_append[i] == '0')
		{
			close(pipefd[1]);
			pipefd[1] = open(cmd->out[i], O_CREAT | O_APPEND | O_WRONLY);
		}
		else
		{
			close(pipefd[1]);
			pipefd[1] = open(cmd->out[i], O_CREAT | O_WRONLY);
		}
		i++;
	}
	return (pipefd[1]);
}

int here_doc(t_exec *cmd, int pipefd[2])
{
	char	*line;

	line = NULL;
	if (cmd->is_here_doc == true)
	{
		line = readline("heredoc> ");
		while (line && ft_strncmp(line, cmd->limiter, ft_strlen(cmd->limiter)) != 0)
		{
			//send to pipe line
			write(pipefd[1], line, ft_strlen(line));
			free(line);
			line = readline("heredoc> ");
		}
		if (line)
		{
			write(pipefd[1], line, ft_strlen(line));
			free(line);
		}
		return (1);
	}
	return (0);
}
