#include "shell.h"

static char	*ft_extract_file(char *to_complete)
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

static char	*ft_extract_path(char *to_complete)
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

static int	is_cmd(char *cmd, int pos)
{
	while (pos >= 0)
	{
		if ((cmd[pos] == '|' || cmd[pos] == '&' || cmd[pos] == ';' || pos == 0)
				&& command_ncomplete(get_quote(), cmd, pos))
			return (1);
		else if (cmd[pos] == ' ')
			pos--;
		else
			break ;
	}
	if (pos == -1)
		return (1);
	return (0);
}

static char	*ft_return_last_element(t_env *e, char *command)
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
		if (pos == -1 || command[pos] == ' ' || command[pos] == '|' ||
				command[pos] == '&' || command[pos] == ';')
		{
			ret = ft_strnew(element);
			ret = ft_strncpy(ret, command + pos + 1, element);
			ret[element] = '\0';
			e->cmd = is_cmd(command, pos);
			break ;
		}
		element++;
	}
	return (ret);
}

void		ft_dynamic_completion(t_env *e, t_elem *elem)
{
	int			line;
	char		*path;
	char		*file;
	char		*to_complete;
	t_history	*h;

	e->cmd = 0;
	h = elem->content;
	if (!h->command_edit)
		h->command_edit = ft_strdup(h->command);
	tputs(e->cd, 1, ft_putchar2);
	to_complete = ft_return_last_element(e, h->command_edit);
	path = ft_extract_path(to_complete);
	file = ft_extract_file(to_complete);
	line = ft_list_corresponding_files(e, path, file, &h->command_edit);
	if (to_complete)
		ft_strdel(&to_complete);
	if (e->complete)
		ft_strdel(&e->complete);
	if (path)
		ft_strdel(&path);
}
