#include "shell.h"

static int	backslash(char *line, int i)
{
	t_quote	*q;

	q = get_quote();
	if (line[i] == 92 && !command_ncomplete(q, line, i))
	{
		if (q->quote && line[i + 1] && line[i + 1] == 39)
			return (1);
		if (q->dquote && line[i + 1] && line[i + 1] == 34)
			return (1);
		if (q->bquote && line[i + 1] && line[i + 1] == 96)
			return (1);
	}
	else if (line[i] == 92 && command_ncomplete(q, line, i))
		return (1);
	return (0);
}

static void	clean2(char **save, int *i, int *j, char *line)
{
	static t_quote	*q = NULL;
	int				start;

	if (!q)
		q = get_quote();
	if (ft_is_quote(line[*i]) || !line[*i + 1] || line[*i] == 92)
	{
		if (q->quote || q->bquote || q->dquote)
			if (i > 0 && line[*i - 1] != 92)
				ft_quote(q, line[*i]);
		if (backslash(line, *i) || (ft_is_quote(line[*i]) && !q->quote &&
					!q->bquote && !q->dquote))
		{
			start = *i - *j == 0 && !ft_is_quote(line[0]) && line[0] != 92
				? 0 : 1;
			if (i == 0 || (i > 0 && line[*i - 1] != 92))
				ft_quote(q, line[*i]);
			*save = ft_strncat(*save, line + *i - *j + start, *j -
					(*j > 1 ? 1 : 0));
			*i += line[*i] == 92 ? 1 : 0;
			*j = 0;
		}
		else if (!line[*i + 1])
			*save = ft_strncat(*save, line + *i - *j, *j + 1);
	}
}

static char	*clean(char *line)
{
	char	*save;
	int		i;
	int		j;

	save = ft_strnew(ft_strlen(line));
	i = 0;
	j = 0;
	while (line && line[i])
	{
		clean2(&save, &i, &j, line);
		i++;
		j++;
	}
	ft_strdel(&line);
	return (save);
}

void		clean_quote(char **line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		line[i] = clean(line[i]);
		i++;
	}
}
