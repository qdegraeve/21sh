#include "shell.h"

char	*ft_remove_old_filename(t_env *e, char **str)
{
	char	*dest;
	int		tmp;

	dest = NULL;
	e->curs_pos--;
	tmp = e->curs_pos;
	while (e->curs_pos >= 0)
	{
		if ((*str)[e->curs_pos] != ' ' && (*str)[e->curs_pos] != '|' &&
				(*str)[e->curs_pos] != '&' && (*str)[e->curs_pos] != ';')
			e->curs_pos--;
		else
			break ;
	}
	dest = ft_strnew(e->curs_max - (tmp - e->curs_pos >= 0) + 1);
	dest = ft_strncpy(dest, *str, e->curs_pos + 1);
	if (tmp < e->curs_max)
		dest = ft_strcat(dest, *str + tmp);
	e->curs_max = e->curs_max - (tmp - e->curs_pos >= 0);
	if (*str)
		ft_strdel(str);
	return (dest);
}

char	*ft_add_new_path(t_env *e, char *path, char *file, char **str)
{
	int		len;
	char	*dest;

	len = ft_strlen(path) + ft_strlen(file) + e->curs_max;
	dest = ft_strnew(len + 1);
	if (e->curs_pos >= 0)
		dest = ft_strncpy(dest, *str, e->curs_pos + 1);
	dest = ft_strcat(dest, path);
	if (path && path[ft_strlen(path) - 1] != '/')
	{
		dest = ft_strcat(dest, "/");
		len++;
	}
	dest = ft_strcat(dest, file);
	if (e->curs_pos < e->curs_max && e->curs_pos >= 0)
		dest = ft_strcat(dest, *str + e->curs_pos);
	e->curs_pos += (len - e->curs_max);
	e->curs_max = len;
	if (*str)
		ft_strdel(str);
	return (dest);
}

void	ft_replace_filename(t_env *e, char *path, char **str)
{
	tputs(tgetstr("up", NULL), 0, ft_putchar2);
	go_to_position(e, *str, 0);
	if (e->complete)
	{
		*str = ft_remove_old_filename(e, str);
		*str = ft_add_new_path(e, path, e->complete, str);
	}
	tputs(e->cd, 1, ft_putchar2);
	ft_putstr(*str);
	tputs(e->sc, 1, ft_putchar2);
	e->curs_max = ft_strlen(*str);
	e->curs_pos = e->curs_max;
}
