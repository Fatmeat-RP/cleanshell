/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:55:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/04/27 12:32:04 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	return_prompt(t_instance *instance)
{
	if (g_status != 0)
		ft_strlcpy(instance->prompt, "\033[31;1mminishell $> \033[0m", 25);
	else
		ft_strlcpy(instance->prompt, "\033[33;1mminishell $> \033[0m", 25);
}

size_t	ft_size(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (i);
	while (array[i] != NULL)
		i++;
	return (i);
}
