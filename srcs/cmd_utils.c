/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:52:21 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/09 02:28:43 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_path(char *cmd, char **envp, size_t j)
{
	char	**paths;
	char	*path;
	char	*part_path;

	while (ft_strnstr(envp[j], "PATH", 4) == 0)
		j++;
	if (envp[j] == NULL)
		return (cmd);
	paths = exec_split(envp[j] + 5, ':');
	j = -1;
	while (paths[++j] != NULL)
	{
		part_path = ft_strjoin(paths[j], "/");
		path = ft_strfreejoin(part_path, cmd);
		if (access(path, F_OK) == 0)
		{
			cmd_free(paths);
			return (path);
		}
		free(path);
	}
	cmd_free(paths);
	return (cmd);
}
