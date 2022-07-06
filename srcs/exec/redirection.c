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

int redirect1(t_exec *cmd, char **envp, int pipefd[2][2])
{
    int i;

    i = 0;
    while (cmd->in[i] != NULL)
    {
        close(pipefd[0][1]);
        pipefd[0][1] = open(cmd->in[i], O_RDONLY);
        i++;
    }
    i = 0;
    while (cmd->out[i] != NULL)
    {
        close(pipefd[1][0]);
        if (cmd->is_append[i] == '0')
        	pipefd[1][0] = open(cmd->out[i], O_CREAT | O_APPEND | O_WRONLY);
        else
            pipefd[1][0] = open(cmd->out[i], O_CREAT | O_WRONLY);
        i++;
    }
    return (0);
}

int redirect2(t_exec *cmd, char **envp, int pipefd[2][2])
{
    int i;

    i = 0;
    while (cmd->in[i] != NULL)
    {
        close(pipefd[1][1]);
        pipefd[1][1] = open(cmd->in[i], O_RDONLY);
        i++;
    }
    i = 0;
    while (cmd->out[i] != NULL)
    {
        close(pipefd[0][0]);
        if (cmd->is_append[i] == '0')
        	pipefd[0][0] = open(cmd->out[i], O_CREAT | O_APPEND | O_WRONLY);
        else
            pipefd[0][0] = open(cmd->out[i], O_CREAT | O_WRONLY);
        i++;
    }
    return (0);
}
