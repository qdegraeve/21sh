#include "shell.h"

void	parser(t_cmds **root)
{
	t_cmds *tmp;

	tmp = *root;
	while (tmp != NULL)
	{
		if (tmp->pipe == 0)
			exec_simple(tmp);
		else
			ft_printf("Piped cmds");
		tmp = tmp->next;
	}
}
