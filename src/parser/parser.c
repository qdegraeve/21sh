#include "shell.h"


static int	is_quote(char *str, int index)
{
	if (index == 0)
	{
		if (str[0] == 34 || str[0] == 39 || str[0] == 96)
			return (1);
	}
	else
	{
		if ((str[index] == 34 || str[index] == 39 || str[index] == 96) &&
				str[index - 1] != '\\')
			return (1);
	}
	return (0);
}

static char *clean(char *line)
{
	char	*save;
	int		i;

	save = ft_strnew(ft_strlen(line));
	i = 0;
	while (line && line[i])
	{
		while (line[i] && is_quote(line, i) == 0)
			i++;
		if (i == 0 && is_quote(line, i) == 1)
			i = 0;
		else
			ft_strncat(save, line, i);
		line = &line[i + 1];
	}
	return (save);
}

static void clean_quote(char **line)
{
	int		i;
	int		j;
	int		delete;
	char	*freeme;

	i = 0;
	while (line[i])
	{
		j = 0;
		delete = 0;
		while (line[i][j])
		{
			if (is_quote(line[i], j) == 1)
				delete++;
			j++;
		}
		if (delete > 0)
		{
			freeme = line[i];
			line[i] = clean(line[i]);
			free(freeme);
		}
		i++;
	}
}


void	parser(t_cmds **root, t_builtin *b)
{
	t_cmds *tmp;
	t_cli	my_cli;
	tmp = *root;
	while (tmp != NULL)
	{
		b->argv = NULL;
		my_cli.input = NULL;
		my_cli.output = NULL;
		init_builtin(b, tmp->cmd);
		clean_quote(b->argv);
	//	ft_print_tab(my_cli.cmd);
		if (tmp->input)
		{
			my_cli.input= str_to_argv(tmp->input);
			clean_quote(my_cli.input);
	//		ft_print_tab(my_cli.input);
		}
		if (tmp->output)
		{
			my_cli.output = str_to_argv(tmp->output);
			clean_quote(my_cli.output);
		//	ft_print_tab(my_cli.output);
		}
		get_command(b->argv[0], b);
		if (b->path && tmp->pipe == 0)
			exec_simple(my_cli, b);
		tmp = tmp->next;
	}
}
