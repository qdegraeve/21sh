#include "shell.h"

char	*ft_remove_old_filename(t_env *e, char **str)
{
	char	*dest;
	int		tmp;

	dest = NULL;
	tmp = e->curs_pos;
	while (e->curs_pos > 0)
	{
		if ((*str)[e->curs_pos] != ' ')
			e->curs_pos--;
		else
			break ;
	}
	dest = ft_strnew(e->curs_max - (tmp - e->curs_pos) + 1);
	dest = ft_strncpy(dest, *str, e->curs_pos + 1);
	if (tmp < e->curs_max)
		dest = ft_strcat(dest, *str + tmp);
	e->curs_max = e->curs_max - (tmp - e->curs_pos) + 1;
	if (*str)
		ft_strdel(str);
	return (dest);
}

char	*ft_add_new_path(t_env *e, char *path, char *file, char **str)
{
	int		len;
	char	*dest;

	len = ft_strlen(path) + ft_strlen(file) + e->curs_max;
	dest = ft_strnew(len + 2);
	dest = ft_strncpy(dest, *str, e->curs_pos + 1);
	dest = ft_strcat(dest, path);
	if (path && path[ft_strlen(path) - 1] != '/')
	{
		dest = ft_strcat(dest, "/");
		len++;
	}
	dest = ft_strcat(dest, file);
	if (e->curs_pos < e->curs_max)
		dest = ft_strcat(dest, *str + e->curs_pos);
	e->curs_pos += (len - e->curs_max);
	e->curs_max = len;
	if (*str)
		ft_strdel(str);
	return (dest);
}

void	ft_replace_filename(t_env *e, char *path, char *file, char **str)
{
	DIR				*repository;
	struct dirent	*content;

	ft_restore_cursor_position(e, *str, 1);
	go_to_position(e, *str, 0);
	*str = ft_remove_old_filename(e, str);
	repository = path == NULL ? opendir(".") : opendir(path);
	while ((content = readdir(repository)) != NULL)
	{
		if (ft_strnstr(content->d_name, file, ft_strlen(file)) != NULL)
			*str = ft_add_new_path(e, path, content->d_name, str);
	}
	tputs(e->cd, 1, ft_putchar2);
	ft_putstr(*str);
	tputs(e->sc, 1, ft_putchar2);
	e->curs_pos = e->curs_max;
	closedir(repository);
}
