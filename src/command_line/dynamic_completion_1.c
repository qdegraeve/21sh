#include "shell.h"

static char	*ft_corresponding_files2(char **tmp, char *name, char *path)
{
	char	*dest;
	DIR		*tmp2;
	char	*tmp3;

	dest = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	*tmp = triple_join(*tmp, " ", name, 1);
	tmp3 = triple_join(path, (path ? "/" : NULL), name, 0);
	if ((tmp2 = opendir(tmp3)) != NULL)
	{
		*tmp = ft_cjoin(*tmp, ft_strdup("/"));
		closedir(tmp2);
	}
	if (tmp3)
		ft_strdel(&tmp3);
	return (dest);
}

static int	ft_corresponding_files(t_env *e, char *path, char *file)
{
	int				match;
	DIR				*repository;
	struct dirent	*content;
	char			*tmp;

	tmp = NULL;
	match = 0;
	repository = path == NULL ? opendir(".") : opendir(path);
	if (repository == NULL)
		return (-1);
	while ((content = readdir(repository)) != NULL)
		if (content->d_name[0] != '.' && !ft_strncmp(content->d_name, file,
					ft_strlen(file)))
		{
			match++;
			ft_corresponding_files2(&tmp, content->d_name, path);
		}
	closedir(repository);
	e->choices = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	return (match);
}

static int	ft_corresponding_cmd(t_env *e, char *file)
{
	int				match;
	int				i;
	t_builtin		*b;
	char			*tmp;

	b = get_buil();
	match = 0;
	i = 0;
	tmp = NULL;
	while (b->cmd_hash[i])
	{
		if (ft_strncmp(b->cmd_hash[i], file, ft_strlen(file)) == 0)
		{
			match++;
			tmp = triple_join(tmp, " ", b->cmd_hash[i], 1);
		}
		i++;
	}
	e->choices = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	return (match);
}

static int	no_match(t_env *e, char *str)
{
	int				move;

	move = 0;
	ft_putstr_fd("\nNo match found.", 2);
	tputs(e->up_one, 0, ft_putchar2);
	tputs(e->cr, 0, ft_putchar2);
	if ((move = calc_row(e, str, e->curs_max)))
		tputs(tgoto(e->ri, 0, move), 0, ft_putchar2);
	return (0);
}

int			ft_list_corresponding_files(t_env *e, char *path, char *file,
		char **str)
{
	int		match;

	match = 0;
	if (e->cmd)
		match = ft_corresponding_cmd(e, file);
	else
		match = ft_corresponding_files(e, path, file);
	if (match == 0)
		return (no_match(e, *str));
	ft_putchar('\n');
	if (match > 1)
	{
		term_reset();
		ft_select(e->choices, e->cmd ? 1 : 0);
		term_set();
		if (e->choices)
			clear_tab(&e->choices);
	}
	if (match == 1)
		e->complete = ft_strdup(e->choices[0]);
	ft_replace_filename(e, path, str);
	return (match);
}
