#include "shell.h"

static void run_pipe(t_cmds **root, t_builtin *b)
{
	int		fdes[2];
	pid_t	child = -1;
	t_cmds	*tmp;
	pipe(fdes);
	
	tmp = *root;
	child = fork();
	DEBUG
	if (child == -1)
	{
		ft_printf("Blocado\n");
		close(fdes[0]);
		close(fdes[1]);
	}
	else if (child == 0)
	{
	//	dup2(fdes[1], STDOUT_FILENO);
	//	close(fdes[0]);
		init_builtin(b, tmp->cmd);
		execve(b->path, b->argv, b->env);
	}
	DEBUG
	wait(NULL);
//	dup2(fdes[0], STDIN_FILENO);
//	close(fdes[1]);
//	DEBUG
//	tmp = tmp->next;
//	init_builtin(b, tmp->cmd);
//	execve(b->path, b->argv, b->env);
}

t_cmds		*exec_pipe(t_cmds **root, t_builtin *b)
{
	pid_t child = -1;
	
	child = fork();
	if (child == -1)
		ft_printf("Blocado\n");
	else if (child == 0)
		run_pipe(root, b);
	wait(NULL);
	return (((*root)->next)->next);
}
