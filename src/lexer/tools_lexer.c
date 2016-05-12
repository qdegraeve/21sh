#include "lexer.h"

void	add_cmds(char *str, int pipe, t_cmds **root)
{
	t_cmds *tmp;
	t_cmds *new;

	new = *root;
	tmp = (t_cmds*)malloc(sizeof(t_cmds));
	tmp->cmd = str;
	tmp->pipe = pipe;
	tmp->input = NULL;
	tmp->output = NULL;
	tmp->next = NULL;
	if (!new)
		*root = tmp;
	else
	{
		while (new->next)
			new = new->next;
		new->next = tmp;
	}
}

void	add_io(char *str, t_io **io)
{
	t_io *tmp;
	t_io *new;

	new = *io;
	tmp = (t_io*)malloc(sizeof(t_io));
	tmp->str = str;
	tmp->next = NULL;
	if (!new)
		*io = tmp;
	else
	{
		while (new->next)
			new = new->next;
		new->next = tmp;
	}
}

void debug_lexer(t_cmds **tmp)
{
	t_cmds *root;
	t_io	*io;

	root = *tmp;
	while (root != NULL)
	{
		ft_printf("CMDS = %s\n", root->cmd);
		if (root->input != NULL)
		{
			io = root->input;
			while (io != NULL)
			{
			ft_printf("\tINPUT = %s\n", io->str);
			io = io->next;
			}
		}
		if (root->output != NULL)
		{
			io = root->output;
			while (io != NULL)
			{
				ft_printf("\toutput = %s\n", io->str);
				io = io->next;
			}
		}
		root = root->next;
	}
}
