#include <minishell.h>

t_control_exec	*struct2(t_control_parse *parse, int nb_pipe, char **envp)
{
	t_control_exec	*exec;
	int				i;
	short			in;
	short			out;

	i = 1;
	in = 0;
	out = 0;
	exec = init_exe_list();
	if (test_free(exec, nb_pipe) == -1)
		return (NULL);
//	convert_struct(parse, exec, nb_pipe);
	while (parse->iter)
	{
		if (parse->iter->flag == PIPE_FLAG)
		{
			exec->iter = exec->iter->next;
			in = 0;
			out = 0;
			i = 1;
		}
		else if (parse->iter->flag == CMD_FLAG)
		{
            exec->iter->cmd[0] = get_path(strdup(parse->iter->elem), envp, 0);
		}
		else if (parse->iter->flag == BUILTIN_FLAG)
			exec->iter->cmd[0] = get_path(strdup(parse->iter->elem), envp, 0);
        else if (parse->iter->flag == ARGS_FLAG)
		{
			exec->iter->cmd[i] = strdup(parse->iter->elem);
			i++;
		}
		else if (parse->iter->flag == REDIR_IN_FLAG)
		{
			parse->iter = parse->iter->next;
			exec->iter->in[in++] = strdup(parse->iter->elem);
		}
		else if (parse->iter->flag == REDIR_OUT_FLAG)
		{
			parse->iter = parse->iter->next;
			exec->iter->out[out] = strdup(parse->iter->elem);
			exec->iter->is_append[out++] = '0';
		}
		else if (parse->iter->flag == REDIR_OUT_ADD_FLAG)
		{
			parse->iter = parse->iter->next;
			exec->iter->out[out] = strdup(parse->iter->elem);
			exec->iter->is_append[out++] = '1';
		}
		else if (parse->iter->flag == HERE_DOC_FLAG)
		{
			parse->iter = parse->iter->next;
			exec->iter->is_here_doc = true;
			exec->iter->limiter = ft_strdup(parse->iter->elem);
		}
		parse->iter = parse->iter->next;
	}
	exec->iter = exec->first;
	return (exec);
}
