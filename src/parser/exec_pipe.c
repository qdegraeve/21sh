#include "shell.h"

t_cmds		*exec_pipe(t_cmds **root)
{
	int		fildes[2];
	t_cmds	*tmp;
	t_cli	*cmd1;
	t_cli	*cmd2;


	tmp = *root;
	pipe(fildes);

}
