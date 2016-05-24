#include "shell.h"

static void run_pipe(t_cmds *tmp, t_builtin *b)
{
	int		fdes[2];
	pid_t	child = -1;
	pipe(fdes);
	
	child = fork();
	if (child == 0)
	{
		dup2(fdes[1], STDOUT_FILENO);
		close(fdes[0]);
		special_char(&tmp->cmd, b);
		init_builtin(b, tmp->cmd);
		clean_quote(b->argv);
		get_command(b->argv[0], b);
		execve(b->path, b->argv, b->env);
		exit(EXIT_FAILURE);
	}
	dup2(fdes[0], STDIN_FILENO);
	close(fdes[1]);
	wait(NULL);
	tmp = tmp->next;
	special_char(&tmp->cmd, b);
	init_builtin(b, tmp->cmd);
	clean_quote(b->argv);
	get_command(b->argv[0], b);
	execve(b->path, b->argv, b->env);
	exit(EXIT_FAILURE);
}

t_cmds		*exec_pipe(t_cmds *tmp, t_builtin *b)
{
	pid_t child;

	child = fork();
	if (child == 0)
		run_pipe(tmp, b);
	wait(NULL);
	return ((tmp->next)->next);
}
