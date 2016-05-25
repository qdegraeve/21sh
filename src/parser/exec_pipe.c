#include "shell.h"

static t_cmds *send_cmds(t_cmds *tmp, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

static int count_pipe(t_cmds *tmp)
{
	int		i;

	i = 0;
	while (tmp && tmp->pipe == 1)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

#include <stdio.h>
static void pipe_handler(t_cmds *tmp, t_builtin *b, int fdes[2], int i, int nb)
{
	pid_t	child = -1;

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
}

static void pipe_manager(t_cmds *tmp, t_builtin *b, int nb)
{
	int		i;
	pid_t	child = -1;
	int		fdes[nb][2];
	t_cli	cmd;

	i = 0;
	while (i <= nb)
	{
		pipe(fdes[i]);
		child = fork();
		if (child == 0)
		{
		pipe_handler(tmp, b, fdes[i], i, nb);
		dup2(fdes[i][0], STDIN_FILENO);
		close(fdes[i][1]);
		wait(NULL);
			tmp = tmp->next;
			special_char(&tmp->cmd, b);
			init_builtin(b, tmp->cmd);
			clean_quote(b->argv);
			get_command(b->argv[0], b);
	//		if (tmp->output)
	///		{
	//			cmd.output = str_to_argv(tmp->output);
	//			clean_quote(cmd.output);
	///			if (get_priority(cmd.output[0]) == -4 && wfile(cmd.output) == 1)
	//				exit(EXIT_FAILURE);
	//			else if (get_priority(cmd.output[0]) == -3 && ape(cmd.output) == 1)
	//				exit(EXIT_FAILURE);
	//		}
			execve(b->path, b->argv, b->env);
		}
			close(fdes[i][1]);
			//close(fdes[i][0]);
			wait(NULL);
			exit(EXIT_FAILURE);
	}
}

t_cmds		*exec_pipe(t_cmds *tmp, t_builtin *b)
{
	int			nbpipe;

	nbpipe = count_pipe(tmp);
	pipe_manager(tmp, b, nbpipe);
	return (send_cmds(tmp, nbpipe));
}
