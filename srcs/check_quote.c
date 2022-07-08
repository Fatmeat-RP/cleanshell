/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:22:32 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/08 22:15:16 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	q_counter(char *line, int q, int i, int tok)
{
	while (line[i])
	{
		if (q == 0)
		{
			if (line[i] == '\'')
				q = 1;
			if (line [i] == '\"')
				q = 2;
		}
		else
		{
			if (line[i] == '\'')
				tok = 1;
			if (line [i] == '\"')
				tok = 2;
			if (q == tok)
			{
				q = 0;
				tok = 0;
			}
		}
		i++;
	}
	return (q);
}

t_bool	check_quote(char *line)
{
	int	q;
	int	i;
	int	tok;

	q = 0;
	i = 0;
	tok = 0;
	if (q_counter(line, q, i, tok) == 1)
	{
		printf("minishel: syntax error near unexpected token `\'\'\n");
		return (false);
	}
	if (q_counter(line, q, i, tok) == 2)
	{
		printf("minishell: syntax error near unexpected token `\"\'\n");
		return (false);
	}
	return (true);
}
