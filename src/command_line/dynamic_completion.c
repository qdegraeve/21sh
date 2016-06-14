#include "shell.h"

char	*ft_extract_file(char *to_complete)
{
	char	*ret;

	ret = NULL;
	ret = ft_strrchr(to_complete, '/');
	if (ret == NULL)
		return (to_complete);
	if (ret[0] == '\0')
		return (NULL);
	return (ret + 1);
}

char	*ft_extract_path(char *to_complete)
{
	int		pos;
	int		end_of_path;
	char	*path;

	pos = 0;
	end_of_path = -1;
	while (to_complete[pos])
	{
		if (to_complete[pos] == '/')
			end_of_path = pos;
		pos++;
	}
	if (end_of_path == -1)
		return (NULL);
	else if (end_of_path == 0)
		end_of_path++;
	path = ft_strsub(to_complete, 0, end_of_path);
	path[ft_strlen(path)] = '\0';
	return (path);
}

char	*ft_return_last_element(t_env *e, char *command)
{
	int		element;
	int		tmp;
	char	*ret;
	int		pos;

	pos = e->curs_pos;
	element = 0;
	tmp = 0;
	ret = NULL;
	while (pos-- > 0)
	{
		if (command[pos] == ' ' || command[pos] == '|' || command[pos] == '&'
				|| command[pos] == ';' || pos == 0)
		{
			ret = ft_strnew(element);
			ret = ft_strncpy(ret, command + pos + (pos ? 1 : 0), element);
			ret[element]= '\0';
			if (command[pos] == ' ')
				e->cmd++;
			break;
		}
		element++;
	}
	return (ret);
}

int		ft_corresponding_files(t_env *e, char *path, char *file)
{
	int				match;
	DIR				*repository;
	DIR				*tmp2;
	struct dirent	*content;
	char			*tmp;

	tmp = NULL;
	match = 0;
	repository = path == NULL ? opendir(".") : opendir(path);
	if (repository == NULL)
		return (-1);
	while ((content = readdir(repository)) != NULL)
		if (ft_strnstr(content->d_name, file, ft_strlen(file)) != NULL)
		{
			match++;
			tmp = triple_join(tmp, " ", content->d_name, 1);
			if ((tmp2 = opendir(triple_join(path, (path ? "/" : NULL), content->d_name, 0))) != NULL)
			{
				tmp = ft_cjoin(tmp, ft_strdup("/"));
				closedir(tmp2);
			}
		}
	closedir(repository);
	e->choices = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	return (match);
}

int		ft_corresponding_cmd(t_env *e, char *file)
{
	int				match;
	int				i;
	t_builtin		*b = NULL;
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

int		ft_list_corresponding_files(t_env *e, char *path, char *file, char **str)
{
	int				match;

	match = 0;
	if (e->cmd)
		match = ft_corresponding_files(e, path, file);
	else
		match = ft_corresponding_cmd(e, file);
	if (match == 0)
	{
		ft_putstr_fd("\nNo match found.", 2);
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 1, ft_putchar2);
		return (match);
	}
	tputs(e->rc, 0, ft_putchar2);
	ft_putchar('\n');
	if (match > 1)
	{
		term_reset();
		ft_select(e->choices, e->cmd ? 0 : 1);
		term_set();
		ft_putstr(*str);
		tputs(e->sc, 0, ft_putchar2);
		go_to_position(e, *str, e->curs_pos);
	}
	if (match == 1)
		e->complete = ft_strdup(e->choices[0]);
	ft_replace_filename(e, path, str);
	return (match);
}

void	ft_restore_cursor_position(t_env *e, char *command, int line)
{
	int		column;
	column = ft_strlen(command) + e->prompt_len;
	tputs(tgoto(e->up, 0, line + 1), 0, ft_putchar2);
	tputs(tgoto(e->ri, 0, column), 0, ft_putchar2);
}

void	ft_dynamic_completion(t_env *e, t_elem *elem)
{
	int		line;
	char	*path;
	char	*file;
	char	*to_complete;
	t_history		*h;

	e->cmd = 0;
	h = elem->content;
	if (!h->command_edit)
		h->command_edit = ft_strdup(h->command);
	tputs(e->cd, 1, ft_putchar2);
	to_complete = ft_return_last_element(e, h->command_edit);
	path = ft_extract_path(to_complete);
	file = ft_extract_file(to_complete);
	line = ft_list_corresponding_files(e, path, file, &h->command_edit);
	//ft_printf("\ncomplete == [%s], file == [%s], path == [%s]\n", to_complete, file, path);
	if (to_complete)
		ft_strdel(&to_complete);
	if (e->choices)
		clear_tab(&e->choices);
	if (e->complete)
		ft_strdel(&e->complete);
	free(path);
}
