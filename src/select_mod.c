#include "shell.h"

static void	ft_highlight_char(t_env *e, char *str, int input)
{
	if (str[e->curs_pos] != '\n')
	{
		if ((e->sel > 1 && input == KRIGHT) || (e->sel < 0 && input == KLEFT)
				|| !e->sel)
			tputs(tgetstr("mr", NULL), 1, ft_putchar2);
		tputs(tgetstr("dc", NULL), 1, ft_putchar2);
		tputs(tgetstr("im", NULL), 1, ft_putchar2);
		ft_putchar(str[e->curs_pos]);
		tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, ft_putchar2);
		tputs(tgetstr("ei", NULL), 1, ft_putchar2);
		tputs(tgetstr("me", NULL), 1, ft_putchar2);
	}
}

void		select_mod(t_env *e, int input, t_elem **elem)
{
	t_history	*h;
	char		*str;

	h = (*elem)->content;
	str = ft_strlen(h->command_edit) > 0 ? h->command_edit : h->command;
	if (!e->sel)
	{
		ft_highlight_char(e, str, input);
		e->sel++;
	}
	else if (e->sel != 0 && input == SEL_OPT)
	{
		go_to_position(e, str, 0);
		ft_putstr(str);
		go_to_position(e, str, e->curs_pos);
		e->sel = 0;
	}
	else if ((input == KLEFT && e->curs_pos) || (input == KRIGHT &&
				e->curs_pos < e->curs_max))
	{
		e->sel += input == KLEFT ? -1 : 1;
		if (e->sel == 0)
			e->sel = input == KLEFT ? -1 : 1;
		ft_highlight_char(e, str, input);
		go_to_position(e, str, input == KLEFT ? e->curs_pos - 1
				: e->curs_pos + 1);
		e->curs_pos += input == KLEFT ? -1 : 1;
	}
	else if (input == CUT_OPT)
	{
		copy_paste_mod(e, input, elem);
		e->sel = 0;
	}
}
