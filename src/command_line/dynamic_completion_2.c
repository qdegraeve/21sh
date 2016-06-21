#include "shell.h"

static char	*ft_remove_old_filename(t_env *e, char **str)
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
		dest = ft_strcat(dest, *str + tmp + 1);
	e->curs_max = ft_strlen(dest);
	if (*str)
		ft_strdel(str);
	return (dest);
}

static void	ft_add_new_path2(char *path, char **file, char **dest, int len_path)
{
	int		i;

	i = 0;
	while (file && file[i])
	{
		*dest = ft_strcat(*dest, path);
		*dest = ft_strcat(*dest, file[i]);
		i++;
		*dest = i != len_path ? ft_strcat(*dest, " ") : *dest;
	}
}

static char	*ft_add_new_path(t_env *e, char *path, char **file, char **str)
{
	int		len;
	char	*dest;
	int		i;
	int		len_path;

	i = 0;
	len = 0;
	if (path && path[ft_strlen(path) - 1] != '/')
		path = ft_strjoin(path, "/");
	len_path = ft_strlen(path);
	while (file && file[i])
		len += (len_path + ft_strlen(file[i++]) + (len ? 1 : 0));
	len += e->curs_max;
	dest = ft_strnew(len);
	len_path = i;
	if (e->curs_pos >= 0)
		dest = ft_strncpy(dest, *str, e->curs_pos + 1);
	ft_add_new_path2(path, file, &dest, len_path);
	if (e->curs_pos < e->curs_max && e->curs_pos >= 0)
		dest = ft_strcat(dest, *str + e->curs_pos + 1);
	e->curs_pos += (len - e->curs_max);
	e->curs_max = len;
	if (*str)
		ft_strdel(str);
	return (dest);
}

void		ft_replace_filename(t_env *e, char *path, char **str)
{
	int		tmp;

	tmp = 0;
	tputs(e->up_one, 0, ft_putchar2);
	if (e->curs_pos > 0)
		go_to_position(e, *str, 0);
	if (e->complete)
	{
		*str = ft_remove_old_filename(e, str);
		e->choices = ft_strsplit(e->complete, ' ');
		*str = ft_add_new_path(e, path, e->choices, str);
		if (e->choices)
			clear_tab(&e->choices);
	}
	ft_putstr(*str);
	tputs(e->sc, 0, ft_putchar2);
	tmp = e->curs_pos + 1;
	e->curs_pos = e->curs_max;
	if (e->curs_pos)
		go_to_position(e, *str, tmp);
	e->curs_pos = (e->curs_pos && e->complete) ? tmp : tmp - 1;
}
