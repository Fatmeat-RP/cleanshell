#include <minishell.h>

void	exec_cleaner(t_control_exec *exec)
{
	if (!exec)
		return ;
	exec->iter = exec->first;
	while (exec->first != NULL)
	{
		exec->iter = exec->first->next;
	//	tab_cleaner(exec->first->in);
	//	tab_cleaner(exec->first->out);
	//	free(exec->first->is_append);
	//	free(exec->first->limiter);
		free(exec->first);
		exec->first = exec->iter;
	}
	free(exec);
}

int	control_parse(t_control_parse *truct)
{
	if (!truct)
		return (-1);
	if (!truct->first)
	{
		free(truct);
		return (-1);
	}
	return (0);
}

int	test_free(t_control_exec *exec, int nb_pipe)
{
	if (!exec)
		return (-1);
	exec->first = init_exe();
	exec->iter = exec->first;
	if (!exec->first)
	{
		free (exec);
		return (-1);
	}
	while (nb_pipe != 0)
	{
		if (exec_add_back(exec, init_exe()))
		{
			exec_cleaner(exec);
			return (-1);
		}
		nb_pipe--;
	}
	return (0);
}

int	free_instance(t_instance *instance, int i)
{
	free(instance->prompt);
	free(instance);
	return (i);
}
