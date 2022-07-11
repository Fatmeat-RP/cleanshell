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

t_control_exec	*structurize(t_control_parse *parse_list, t_instance *instance)
{
	t_control_exec	*exes;

	exes = NULL;
	exes = init_exe_list(exes);
	parse_list->iter = parse_list->first;
	while (exec_add_back(exes, create_exec_from_parsec(parse_list, instance)))
		printf("oui\n");
	return (exes);
}

int	check_test(t_parse *node)
{
	if (node == NULL)
		return (-1);
	if (node->flag == PIPE_FLAG)
		return (0);
	return (1);
}

t_exec *create_exec_from_parsec(t_control_parse *parse_list, t_instance *instance)
{
	t_exec		*node;
	size_t		i;
    size_t      j;

	i = 0;
    j = 1;
	if (parse_list->iter == NULL)
        return(NULL);
	if (parse_list->iter->flag == PARSE_ERROR || parse_list->iter->flag == PIPE_ERROR
        || parse_list->iter->flag == EMPTY_LINE)
        return(NULL);
	node = init_exe();
	printf("-1");
	sleep(1);
	if (!parse_list->iter->next)
	{
		node->cmd[0] = get_path(strdup(parse_list->iter->elem), instance->envp, 0);
		parse_list->iter = NULL;
	}
	printf("0");
	sleep(1);
	while (check_test(parse_list->iter))
	{
		printf("1");
		sleep(1);
        if (parse_list->iter->flag == CMD_FLAG)
            node->cmd[0] = get_path(strdup(parse_list->iter->elem), instance->envp, 0);
		sleep(14);
		if (parse_list->iter->flag == BUILTIN_FLAG)
			node->cmd[0] = get_path(strdup(parse_list->iter->elem), instance->envp, 0);;
        if (parse_list->iter->flag == ARGS_FLAG)
		{
			node->cmd[j] = strdup(parse_list->iter->elem);
            j++;
		}
		printf("3");
		sleep(1);
        allocator_counter(parse_list, node);
		i++;
	}
	if (parse_list->iter)
		if (parse_list->iter->flag == PIPE_FLAG)
			node->is_pipe = true;
	return (node);
}

int allocator_counter(t_control_parse *parse_list, t_exec *node)
{
    int     in;
	int		j;
    int     out;
    void    *ptr;

    ptr = parse;
    in = 0;
    out = 0;
	j = 0;
    while (parse_list->iter->flag != PIPE_FLAG && parse_list->iter->next)
    {
        if (parse_list->iter->flag == REDIR_IN_FLAG)
            in++;
        if (parse_list->iter->flag == REDIR_OUT_FLAG)
            out++;
        if (parse_list->iter->flag == REDIR_OUT_ADD_FLAG)
            out++;
		if (parse_list->iter->flag == HERE_DOC_FLAG)
			node->is_here_doc = true;
		j++;
        parse_list->iter = parse_list->iter->next;
		printf("oui%i::%i::%p\n", in, out, parse_list->iter);
//		if (!parse_list->iter->next && ((out + in) >= (j/2)))
//			return(-1);
    }
    parse_list->iter = ptr;
	if (in == 0 || out == 0)
		return (0);
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
    while (parse_list->iter->next->flag != PIPE_FLAG && parse_list->iter)
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
        if (parse_list->iter->flag == HERE_DOC_FLAG)
        {
			parse_list->iter = parse_list->iter->next;
            node->limiter = ft_strdup(parse_list->iter->elem);
        }
        parse_list->iter = parse_list->iter->next;
    }
    node->out[out] = NULL;
    node->in[in] = NULL;
    node->is_append[out] = 0;
    return (0);
}