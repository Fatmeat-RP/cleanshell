/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cben-bar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:52:20 by cben-bar          #+#    #+#             */
/*   Updated: 2022/07/06 19:34:20 by cben-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char			*line;
	char			**line_tab;
	t_control_parse	*parsing;
	size_t			i;
	int				q;

	parsing = NULL;
	(void)ac;
	(void)av;
//	line = "\"|<infile $cat -e $|\" $wc -l >>'$'hey ";
//	line = "\"|<infile cat -e |\" wc \'-l\' >> out << delim  | \"ls -la\" | echo \'oui\' < oui.txt hoho<<ici\'>>   \'hey ";
//	line = "cat jeanette\'fleur\' | cat  \"maman\" blurp\"Jean-Jacques\"ouioui\'non\'ici | cat \"flop\"jardin | cat $USER | cat 012$XPC_FLAGS $LGNAME$USER | cat \"soleil\"noir ";
//	line = "cat \"$?\"";
	line = "cat \"$SSH_AUTH_SOCK\" | echo $XPC_FLAGS$PWD $TERM $LC_CTYPE | ls -la | echo $$$";
//	line = "\"$USER $PAGER$USER |cat\" \'$i\' \" $$merdekh\" \"$COLORFGBG\" 012$XPC_FLAGS $HOME \"$LESS$SHLVL\"";
	i = 0;
	q = 0;
	printf("LINE MAIN =%s\n\n", line);
	if (first_check(line))
	{
		line_tab = ft_split_it(line, '|', i, q);
		parsing = set_parseur(parsing, line_tab, envp);
		if (!printer_error(parsing))
			printf("PAS D'EXEC\n");
		parsing_printer(parsing);
		cleaner(parsing);
	}
	return (0);
}
