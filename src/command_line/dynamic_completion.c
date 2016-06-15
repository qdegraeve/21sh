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

int		is_cmd(char *command, int pos)
{
	while (pos >= 0)
	{
		if ((command[pos] == '|' || command[pos] == '&' || command[pos] == ';'
					|| pos == 0) && command_ncomplete(get_quote(), command, pos))
			return (1);
		else if (command[pos] == ' ')
			pos--;
		else
			break ;
	}
	if (pos == -1)
		return (1);
	return (0);
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
		while (pos-- >= 0)
		{
			if (pos == -1 || command[pos] == ' ' || command[pos] == '|' || command[pos] == '&'
					|| command[pos] == ';')
			{
				ret = ft_strnew(element);
				ret = ft_strncpy(ret, command + pos + 1, element);
				ret[element]= '\0';
				e->cmd = is_cmd(command, pos);
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
			if (content->d_name[0] != '.' && !ft_strncmp(content->d_name, file, ft_strlen(file)))
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
	int				move;

	match = 0;
	move = 0;
	if (e->cmd)
		match = ft_corresponding_cmd(e, file);
	else
		match = ft_corresponding_files(e, path, file);
	if (match == 0)
	{
		ft_putstr_fd("\nNo match found.", 2);
		tputs(e->up_one, 0, ft_putchar2);
		tputs(e->cr, 0, ft_putchar2);
		if ((move = calc_row(e, *str, e->curs_max)))
			tputs(tgoto(e->ri, 0, move), 0, ft_putchar2);
		return (match);
	}
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
	//	ft_printf("\ncomplete == [%s], file == [%s], path == [%s]\n", to_complete, file, path);
	if (to_complete)
		ft_strdel(&to_complete);
	if (e->complete)
		ft_strdel(&e->complete);
	if (path)
		ft_strdel(&path);
}
