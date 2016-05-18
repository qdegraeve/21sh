#include "shell.h"


void	parser(t_cmds **root)
{
	t_cmds *tmp;
	int		i;
//	char	**line;

	tmp = *root;
	while (tmp != NULL)
	{
		i = 0;
//		if (tmp->pipe == 0)
//			exec_simple(tmp);
//		else
//			ft_printf("Piped cmds");
//		line = custom_ft_strsplit(tmp->cmd, ' ');
//		while (line[i])
//			ft_printf("%s\n", line[i++]);
//		ft_putchar('\n');
		tmp = tmp->next;
	}
}
