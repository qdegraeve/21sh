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

char	*ft_return_last_element(char *command)
{
	int		element;
	int		tmp;
	char	*ret;
	char	**split;

	element = 0;
	tmp = 0;
	split = ft_strsplit(command, ' ');
	while (split[element + 1] != NULL)
		element++;
	ret = ft_strnew(tmp = ft_strlen(split[element]));
	ft_strcpy(ret, split[element]);
	ret[tmp]= '\0';
	clear_tab(&split);
	return (ret);
}

int		ft_list_corresponding_files(t_env *e, char *path, char *file, char **str)
{
	int				match;
	DIR				*repository;
	struct dirent	*content;

	match = 0;
	repository = path == NULL ? opendir(".") : opendir(path);
	if (repository == NULL)
		return (-1);
	while ((content = readdir(repository)) != NULL)
		if (ft_strnstr(content->d_name, file, ft_strlen(file)) != NULL)
		{
			match++;
			ft_putchar('\n');
			ft_putstr(content->d_name);
		}
	if (match == 0)
	{
		ft_putstr_fd("\nNo match found.", 2);
		tputs(tgoto(tgetstr("up", NULL), 0, 0), 1, ft_putchar2);
	}
	ft_putchar('\n');
	closedir(repository);
	if (match == 1)
		ft_replace_filename(e, path, file, str);
	return (match);
}

void	ft_restore_cursor_position(t_env *e, char *command, int line)
{
	int		column;
	column = ft_strlen(command) + e->prompt_len;
	tputs(tgoto(e->up, 0, line + 1), 1, ft_putchar2);
	tputs(tgoto(e->ri, 0, column), 1, ft_putchar2);
}

void	ft_dynamic_completion(t_env *e, t_elem *elem)
{
	int		line;
	char	*path;
	char	*file;
	char	*to_complete;
	t_history		*h;

	h = elem->content;
	if (!h->command_edit)
		h->command_edit = ft_strdup(h->command);
	tputs(e->cd, 1, ft_putchar2);
	to_complete = ft_return_last_element(h->command_edit);
	path = ft_extract_path(to_complete);
	file = ft_extract_file(to_complete);
	line = ft_list_corresponding_files(e, path, file, &h->command_edit);
	if (line != 1 && line > -1)
		ft_restore_cursor_position(e, h->command_edit, line);
	free(path);
	free(to_complete);
}
