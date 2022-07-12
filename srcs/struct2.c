#include <minishell.h>

t_control_exec	*struct2(t_control_parse *parse, int nb_pipe)
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
		if (parse->iter->flag == PIPE_FLAG)
		{
			printf("%i\n", i);
			i++;
			exec->iter->is_pipe = true;
			exec->iter = exec->iter->next;
		}
		parse->iter = parse->iter->next;
	}
	return (exec);
}