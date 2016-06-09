#include "shell.h"

void		copy_cut_sel(t_env *e, char **str, t_builtin *b, int input)
{
	char	*dest;
	int		diff;

	dest = NULL;
	e->curs_pos = e->curs_pos + 1 - (e->sel > 0 ? e->sel : 0);
	diff = ft_abs(e->sel);
	if (b->paste)
		ft_strdel(&b->paste);
	b->paste = ft_strncpy(ft_strnew(ft_abs(e->sel)), *str + e->curs_pos, diff);
	if (input == CUT_OPT)
	{
	dest = ft_strnew(e->curs_max - diff);
	dest = ft_strncat(dest, *str, e->curs_pos);
	dest = ft_strncat(dest, *str + e->curs_pos + diff, e->curs_max - (e->curs_pos + diff));
	ft_strdel(&*str);
	*str = dest;
	e->curs_max -= diff;
	e->curs_pos = e->curs_pos;
	}
	go_to_position(e, *str, 0);
	tputs(e->cd, 0, ft_putchar2);
	ft_putstr(*str);
	go_to_position(e, *str, e->curs_pos);
}

void		cut(t_env *e, char **str, t_builtin *b)
{
	char	*dest;

	dest = NULL;
	if (b->paste)
		ft_strdel(&b->paste);
	if (ft_strlen(*str) > 0 && e->curs_pos < e->curs_max)
	{
		dest = ft_strnew(e->curs_pos);
		b->paste = ft_strdup(*str + e->curs_pos);
		go_to_position(e, *str, 0);
		dest = ft_strncat(dest, *str, e->curs_pos);
		e->curs_max = e->curs_pos;
		tputs(e->cd, 0, ft_putchar2);
		ft_putstr(*str);
	}
}

static void	copy(t_env *e, char *str, t_builtin *b)
{
	if (b->paste)
		ft_strdel(&b->paste);
	if (ft_strlen(str) > 0 && e->curs_pos < e->curs_max)
		b->paste = ft_strdup(str + e->curs_pos);
}

static void	paste(t_env *e, char **str, t_builtin *b)
{
	char	*dest;
	int		i;

	i = 0;
	if (!b->paste)
		return ;
	go_to_position(e, *str, 0);
	e->curs_max = ft_strlen(*str) + ft_strlen(b->paste);
	dest = ft_strnew(e->curs_max);
	dest = ft_strncpy(dest, *str, e->curs_pos);
	dest = ft_strcat(dest, b->paste);
	if (e->curs_pos < e->curs_max)
		dest = ft_strcat(dest, *str + e->curs_pos);
	ft_strdel(str);
	*str = dest;
	dest[e->curs_max] = '\0';
	tputs(e->cd, 0, ft_putchar2);
	ft_putstr(*str);
	tputs(e->sc, 0, ft_putchar2);
	e->curs_pos += ft_strlen(b->paste);
	go_to_position(e, *str, e->curs_pos);
}

void		copy_paste_mod(t_env *e, int input, t_elem **elem)
{
	t_history	*h;

	h = (*elem)->content;
	if (input == COPY_OPT && !h->command_edit)
		copy(e, h->command, get_buil());
	else
	{
		if (!h->command_edit)
			h->command_edit = ft_strdup(h->command);
		if (e->sel)
			copy_cut_sel(e, &h->command_edit, get_buil(), input);
		else if (input == CUT_OPT)
			cut(e, &h->command_edit, get_buil());
		else if (input == COPY_OPT)
			copy(e, h->command_edit, get_buil());
		else if (input == PASTE_OPT)
			paste(e, &h->command_edit, get_buil());
	}
}
