#include "shell.h"

static char	*clean(char *line)
{
	char	*save;
	int		i;
	int		j;
	t_quote	*q;

	save = ft_strnew(ft_strlen(line));
	q = get_quote();
	i = 0;
	j = 0;
	while (line && line[i])
	{
		if (ft_is_quote(line[i]) || !line[i + 1] || line[i] == 92)
		{
			if (q->quote || q->bquote || q->dquote)
				if (i > 0 && line[i - 1] != 92)
					ft_quote(q, line[i]);
			if (line[i] == 92 || (ft_is_quote(line[i]) && !q->quote && !q->bquote && !q->dquote))
			{
				if (i == 0 || (i > 0 && line[i - 1] != 92))
					ft_quote(q, line[i]);
				save = ft_strncat(save, line + i - j + 1, j - (j > 0 ? 1 : 0));
				i += line[i] == 92 ? 1 : 0;
				j = 0;
			}
			else if (!line[i + 1])
				save = ft_strncat(save, line + i - j, j + 1);
		}
		i++;
		j++;
	}
	ft_strdel(&line);
	return (save);
}

void	clean_quote(char **line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		line[i] = clean(line[i]);
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
		if (tmp->pipe == 0)
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
			if (b->path)
				exec_simple(my_cli, b);
			tmp = tmp->next;
		}
		else if (tmp->pipe == 1)
			tmp = exec_pipe(tmp, b);
	}
}
