#include "shell.h"

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
	t_cmds *last;

	last = *root;
	while (last->next != NULL)
		last = last->next;
	if (fd == 1 && last->input == NULL)
		last->input = str;
	else if (fd != 1 && last->output == NULL)
		last->output = str;
}

void	debug_lexer(t_cmds **tmp) // fonction de debug a suprimer avec le rendu
{
	t_cmds *root;

	root = *tmp;
	while (root != NULL)
	{
		ft_printf("CMDS = %s\n", root->cmd);
		if (root->input != NULL)
			ft_printf("\tINPUT = %s\n", root->input);
		if (root->output != NULL)
			ft_printf("\toutput = %s\n", root->output);
		if (root->pipe == 1)
			ft_printf("\tIS PIPED \n");
		root = root->next;
	}
}

void	count(int *i, int *total, int counter)
{
	*i = *i + counter;
	*total = *total + counter;
}

int		get_io(char *str)
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

int		space_priority(char *str)
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
