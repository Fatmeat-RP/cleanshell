/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structurize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:36:23 by acarle-m          #+#    #+#             */
/*   Updated: 2022/05/10 15:48:30 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_control_exec	*structurize(t_control_parse *parse_list, t_instance *instance, t_parse *first)
{
	t_control_exec	*exes;

	exes = NULL;
	exes = init_exe_list(exes);
	parse_list->iter = first;
	while (exec_add_back(exes, create_exec_from_parsec(parse_list, instance)))
		printf("oui\n");
	return (exes);
}

t_exec *create_exec_from_parsec(t_control_parse *parse_list, t_instance *instance)
{
	t_exec		*node;
	size_t		i;
    size_t      j;

	i = 0;
    j = 1;
	if (parse_list == NULL)
        return(NULL);
	if (parse_list->first->flag == PARSE_ERROR || parse_list->first->flag == PIPE_ERROR
        || parse_list->first->flag == EMPTY_LINE)
        return(NULL);
	node = init_exe();
	while (parse_list->iter->flag != PIPE_FLAG && parse_list->iter != NULL)
	{
        if (parse_list->iter->flag == CMD_FLAG || parse_list->iter->flag == BUILTIN_FLAG)
        {
			node->cmd[0] = strdup(parse_list->iter->elem);
            node->cmd[0] = get_path(node->cmd[0], instance->envp, 0);
        }
        if (parse_list->iter->flag == ARGS_FLAG)
		{
			node->cmd[j] = strdup(parse_list->iter->elem);
            j++;
		}
        allocator_counter(parse_list, node);
        parse_list->iter = parse_list->iter->next;
		i++;
	}
	if (parse_list->iter->flag == PIPE_FLAG)
		node->is_pipe = true;
	return (node);
}

int allocator_counter(t_control_parse *parse_list, t_exec *node)
{
    int     in;
    int     out;
    void    *ptr;

    ptr = parse;
    in = 0;
    out = 0;
    while (parse_list->iter->flag != PIPE_FLAG)
    {
        if (parse_list->iter->flag == REDIR_IN_FLAG)
            in++;
        if (parse_list->iter->flag == REDIR_OUT_FLAG)
            out++;
        if (parse_list->iter->flag == REDIR_OUT_ADD_FLAG)
            out++;
		printf("oui%i::%i::%p\n", in, out, parse_list->iter->next);
        parse_list->iter = parse_list->iter->next;
    }
    parse_list->iter = ptr;
    node->in = malloc(sizeof(char *) * in + 1);
    if (!(node->in))
        return(-1);
    node->out = malloc(sizeof(char *) * out + 1);
    if (!(node->out))
        return((free(node->in), -1));
    in = 0;
    node->is_append = malloc(out + 1);
    if (!(node->is_append))
        return((free(node->in), -1) && (free(node->out), -1));
    out = 0;
    while (parse_list->iter->next->flag != PIPE_FLAG)
    {
        if (parse_list->iter->flag == REDIR_IN_FLAG)
        { 
            parse_list->iter = parse_list->iter->next;
            node->in[in++] = strdup(parse_list->iter->elem);
        }
        if (parse_list->iter->flag == REDIR_OUT_FLAG)
        {
            parse_list->iter = parse_list->iter->next;
            node->out[out] = strdup(parse_list->iter->elem);
            node->is_append[out++] = '0';
        }
        if (parse_list->iter->flag == REDIR_OUT_ADD_FLAG)
        {
            parse_list->iter = parse_list->iter->next;
            node->out[out] = strdup(parse_list->iter->elem);
            node->is_append[out++] = '1';
        }
        if (parse_list->iter->flag == DELIM_NAME)
        {
            node->is_here_doc = true;
            node->limiter = ft_strdup(parse_list->iter->elem);
        }
        parse_list->iter = parse_list->iter->next;
    }
    node->out[out] = NULL;
    node->in[in] = NULL;
    node->is_append[out] = 0;
    return (0);
}