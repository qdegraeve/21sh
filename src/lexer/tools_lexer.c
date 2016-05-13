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

void	add_io(char *str, t_cmds **root, int fd)
{
	t_io *tmp;
	t_io *new;
	t_cmds *last;

	last = *root;
	while (last->next != NULL)
		last = last->next;
	new = fd == 1 ? last->input : last->output;
	tmp = (t_io*)malloc(sizeof(t_io));
	tmp->str = str;
	tmp->next = NULL;
	if (!new)
		fd == 1 ? (last->input = tmp) : (last->output = tmp);
	else
	{
		while (new->next)
			new = new->next;
		new->next = tmp;
	}
}

void debug_lexer(t_cmds **tmp) // fonction de debug a suprimer avec le rendu
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

void count(int *i, int *total, int counter)
{
	*i = *i + counter;
	*total = *total + counter;
}

int get_io(char *str)
{
	 if (str && str[0] == '|')
		return (2);
	else if (str && str[0] == ';')
		return (1);
	else if (str && str[0] == '>' && str[1] == '>')
		return (-3);
	else if (str && str[0] == '>')
		return (-4);
	else if (str && str[0] == '<' && str[1] == '<')
		return (-2);
	else if (str && str[0] == '<')
		return (-1);
	return (3);
}

int space_priority(char *str)
{
	if (str && str[0] == '>' && str[1] == '>')
		return (2);
	else if (str && str[0] == '>')
		return (1);
	else if (str && str[0] == '<' && str[1] == '<')
		return (2);
	else if (str && str[0] == '<')
		return (1);
	return (0);
}
