/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:39 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/09 01:17:32 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	first_check(char *line)
{
	if (!check_empty_line(line))
		return (false);
	if (!check_quote(line))
		return (false);
	if (!check_first_pipe(line))
		return (false);
	if (!check_last_pipe(line))
		return (false);
	if (!check_last_chev(line))
		return (false);
	if (!check_consec_pipe(line))
		return (false);
	return (true);
}
