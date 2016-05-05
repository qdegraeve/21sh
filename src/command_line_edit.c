#include "shell.h"

char	*string_insert(char *src, char ins, int pos)
{
	char	*dest;
	char	letter[2];
	int		len;

	letter[0] = ins;
	letter[1] = '\0';
	len = ft_strlen(src);
	dest = ft_strnew(len + 1);
	dest = ft_strncpy(dest, src, pos);
	dest = ft_strcat(dest, letter);
	if (pos < len - 1)
		dest = ft_strcat(dest, src + pos);
	dest[len + 1] = '\0';
	if (src)
		ft_strdel(&src);
	return (dest);
}

void	display_command(t_env *e, char input, char *str)
{
	int		i;
	int		j;

	i = ft_strlen(str);
	j = 0;
	go_to_position(e, str, 0);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	ft_putstr_fd(str, e->fd);
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	j = input == 127 ? e->curs_pos - 1 : e->curs_pos + 1;
	e->curs_pos = e->curs_max;
	go_to_position(e, str, j);
	e->curs_pos = j;
}

void	write_char(t_env *e, char input, t_elem *elem)
{
	t_history *h;

	h = elem->content;
	ft_quote(e, input);
	if (!h->command_edit)
		h->command_edit = ft_strdup(h->command);
	h->command_edit = string_insert(h->command_edit, input, e->curs_pos);
	e->curs_max++;
	display_command(e, input, h->command_edit);
}

char	*delete_char(t_env *e, char *src)
{
	char	*dest;
	int		len;

	if (ft_is_quote(src[e->curs_pos - 1]))
		ft_quote(e, src[e->curs_pos - 1]);
	len = ft_strlen(src) - 1;
	dest = ft_strnew(len);
	dest = ft_strncpy(dest, src, e->curs_pos -1);
	dest = ft_strcat(dest, src + e->curs_pos);
	dest[len] = '\0';
	if (src)
		ft_strdel(&src);
	e->curs_max--;
	display_command(e, 127, dest);
	return (dest);
}

t_elem	*command_memory(t_env *e, int input, t_list *lst, t_elem *elem)
{
	t_history	*h;
	char		*str;

	h = elem->content;
	str = ft_strlen(h->command_edit) > 0 ? h->command_edit : h->command;
	if (e->curs_pos)
		move_cursor_line(e, HOME, str);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	if (input == KUP && elem != lst->head)
		elem = elem->prev;
	else if (input == KDOWN && elem != lst->tail)
		elem = elem->next;
	h = elem->content;
	str = h->command_edit ? h->command_edit : h->command;
	e->curs_max = 0;
	if (str)
	{
		ft_putstr(str);
		e->curs_max = ft_strlen(str);
	}
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	e->curs_pos = e->curs_max;
	return (elem);
}

