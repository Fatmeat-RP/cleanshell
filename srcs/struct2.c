#include <minishell.h>

t_control_exec	*struct2(t_control_parse *parse)
{
	t_control_exec	*exec;
	int				*nb_pipe;

	nb_pipe = 0;
	exec = init_exe_list();
	nb_pipe = pipe_counter(parse);
	exec->first = init_exe();
	while (nb_pipe != 0)
	{
		exec_add_back(exec, init_exe());
		nb_pipe--;
	}
	printf("%p :: %p :: %p\n", exec, exec->first, exec->iter);
	printf("%p :: %p :: %p :: %p\n", parse, parse->first, parse->first->next, parse->iter);
	free(exec);
	return (exec);
}