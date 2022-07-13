#include <minishell.h>

t_control_exec	*struct2(t_control_parse *parse, int nb_pipe, char **envp)
{
	t_control_exec	*exec;
	int				i;

	i = 1;
	exec = init_exe_list();
	if (test_free(exec, nb_pipe) == -1)
		return (NULL);
//	convert_struct(parse, exec, nb_pipe);
	while (parse->iter)
	{
//		allocator_counter(parse, exec->iter);
		if (parse->iter->flag == PIPE_FLAG)
		{
			exec->iter = exec->iter->next;
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
		parse->iter = parse->iter->next;
	}
	exec->iter = exec->first;
	return (exec);
}