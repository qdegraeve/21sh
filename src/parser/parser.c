#include "shell.h"

static int	is_quote(char *str, int i)
{
	if (i == 0)
	{
		if (str[0] == 34 || str[0] == 39 || str[0] == 96)
			return (1);
		// ici verifier str && dstr[0] == '/'
	}
	else
	{
		if ((str[i] == 34 || str[i] == 39 || str[i] == 96) &&
				str[i - 1] != '\\')
			return (1);
		// ici verifier str && dstr[0] == '/'
	}
	return (0);
}

static char	*clean(char *line)
{
	char	*save;
	int		i;

	save = ft_strnew(ft_strlen(line));
	i = 0;
	while (line && line[i])
	{
		while (line[i] && is_quote(line, i) == 0)
			i++;
		if (!(i == 0 && is_quote(line, i) == 1))
			ft_strncat(save, line, i);
		line = &line[i + 1];
	}
	return (save);
}

static void	clean_quote(char **line)
{
	int		i;
	int		j;
	int		delete;
	char	*freeme;

	i = 0;
	while (line && line[i])
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

void		parser(t_cmds **root, t_builtin *b)
{
	t_cmds	*tmp;
	t_cli	my_cli;

	tmp = *root;
	while (tmp != NULL)
	{
		ft_bzero(&my_cli, sizeof(t_cli));
		special_char(&tmp->cmd, b);
		init_builtin(b, tmp->cmd);
		if (!b->argv)
			return ;
		clean_quote(b->argv);
		if (tmp->input)
		{
			my_cli.input = str_to_argv(tmp->input);
			clean_quote(my_cli.input);
		}
		if (tmp->output)
		{
			my_cli.output = str_to_argv(tmp->output);
			clean_quote(my_cli.output);
		}
		get_command(b->argv[0], b);
		if (b->path && tmp->pipe == 0)
			exec_simple(my_cli, b);
		tmp = tmp->next;
	}
}
