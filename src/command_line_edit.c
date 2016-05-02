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

void	write_char(t_env *e, char input, t_elem *elem)
{
	t_history *h;

	h = elem->content;
	ft_quote(e, input);
	if (!h->command_edit)
		h->command_edit = ft_strdup(h->command);
	if (e->curs_max != e->curs_pos)
		tputs(tgetstr("im", NULL), 0, ft_putchar2);
	ft_putchar_fd(input, e->fd);
	if (e->curs_max != e->curs_pos)
		tputs(tgetstr("ei", NULL), 0, ft_putchar2);
	h->command_edit = string_insert(h->command_edit, input, e->curs_pos);
	e->curs_max++;
	e->curs_pos++;
}

char	*delete_char(t_env *e, char *src)
{
	char	*dest;
	int		len;

	len = ft_strlen(src);
	dest = ft_strnew(len);
	dest = ft_strncpy(dest, src, e->curs_pos -1);
	dest = ft_strcat(dest, src + e->curs_pos);
	dest[len] = '\0';
	if (src)
			ft_strdel(&src);
	tputs(tgetstr("le", NULL), 0, ft_putchar2);
	tputs(tgetstr("dc", NULL), 0, ft_putchar2);
	e->curs_pos--;
	e->curs_max--;
	return (dest);
}

t_elem	*command_memory(t_env *e, int input, t_list *lst, t_elem *elem)
{
	tputs(tgetstr("rc", NULL), 0, ft_putchar2);
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	if (input == KUP && elem != lst->head)
		elem = elem->prev;
	else if (input == KDOWN && elem != lst->tail)
		elem = elem->next;
	e->curs_max = 0;
	if (((t_history*)elem->content)->command_edit)
	{
		ft_putstr(((t_history*)elem->content)->command_edit);
		e->curs_max = ft_strlen(((t_history*)elem->content)->command_edit);
	}
	else if (((t_history*)elem->content)->command)
	{
		ft_putstr(((t_history*)elem->content)->command);
		e->curs_max = ft_strlen(((t_history*)elem->content)->command);
	}
	e->curs_pos = e->curs_max;
	return (elem);
}
