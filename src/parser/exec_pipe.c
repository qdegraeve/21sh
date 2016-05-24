#include "shell.h"

static void run_pipe(t_cmds *tmp, t_builtin *b)
{
	int		fdes[2];
	pid_t	child = -1;
	t_cli	cmd;

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
	}
	dup2(fdes[0], STDIN_FILENO);
	close(fdes[1]);
	wait(NULL);
	tmp = tmp->next;
	special_char(&tmp->cmd, b);
	init_builtin(b, tmp->cmd);
	clean_quote(b->argv);
	get_command(b->argv[0], b);
	if (tmp->output)
	{
		cmd.output = str_to_argv(tmp->output);
		clean_quote(cmd.output);
		if (get_priority(cmd.output[0]) == -4 && wfile(cmd.output) == 1)
			exit(EXIT_FAILURE);
		else if (get_priority(cmd.output[0]) == -3 && ape(cmd.output) == 1)
			exit(EXIT_FAILURE);
	}
	execve(b->path, b->argv, b->env);
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
