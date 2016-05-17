#include "shell.h"

int		calc_row(t_env *e, char *str, int pos)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	ret = 0;
	while (i < pos && str[i] && str[i] != '\n')
		i++;
	ret += (i + e->prompt_len) % e->width;
	while (i < pos && str[i])
	{
		j = 0;
		if (str[i] == '\n')
		{
			i++;
			ret = 0;
		}
		while (str[i] != '\n' && i++ < pos)
			j++;
		ret += j % e->width;
	}
	return (ret);
}

int		calc_line(t_env *e, char *str, int pos)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	ret = 0;
	while (i < pos && str[i] && str[i] != '\n')
		i++;
	ret += (i + e->prompt_len) / e->width;
	while (i < pos && str[i])
	{
		j = 0;
		if (str[i] == '\n')
		{
			i++;
			ret++;
		}
		while (str[i] != '\n' && i++ < pos)
			j++;
		ret += j / e->width;
	}
	return (ret);
}

void	go_to_position(t_env *e, char *str, int position)
{
	int		move;

	move = 0;
	tputs(tgoto(tgetstr("LE", NULL), 0, e->width), 0, ft_putchar2);
	if ((move = calc_line(e, str, e->curs_pos)))
	{
		tputs(tgoto(tgetstr("UP", NULL), 0, move), 0, ft_putchar2);
	}
	if (!position)
		tputs(tgoto(tgetstr("RI", NULL), 0, e->prompt_len), 0, ft_putchar2);
	if (position && (move = calc_line(e, str, position)))
		tputs(tgoto(tgetstr("DO", NULL), 0, move), 0, ft_putchar2);
	if (position && (move = calc_row(e, str, position)))
		tputs(tgoto(tgetstr("RI", NULL), 0, move), 0, ft_putchar2);
}

void	keys_actions(t_env *e, int i, t_list *lst, t_elem **elem)
{
	t_history		*h;
	char			*str;

	h = (*elem)->content;
	str = ft_strlen(h->command_edit) > 0 ? h->command_edit : h->command;
	if ((i > 31 && i < 127) || (i == 127 && e->curs_pos != 0) ||
			(i == DEL && e->curs_pos < e->curs_max))
		modif_command(e, i, *elem);
	else if (i == 4)
	{
		if (ft_strlen(h->command_edit) == 0 && *elem != lst->tail)
			exec_exit(get_buil());
		else if (!(ft_strlen(h->command_edit)) && *elem == lst->tail)
			exec_exit(get_buil());
	}
	else if ((i == KLEFT && e->curs_pos) || (i == KRIGHT &&
				e->curs_pos < e->curs_max))
	{
		go_to_position(e, str, i == KLEFT ? e->curs_pos - 1 : e->curs_pos + 1);
		e->curs_pos += i == KLEFT ? -1 : 1;
	}
	else if ((i == KUP && (*elem)->prev) || (i == KDOWN && (*elem)->next))
		command_memory(e, i, lst, elem);
	else if (i == END || i == HOME)
		move_cursor_line(e, i, str);
	else if ((i == LEFT_OPT && e->curs_pos > 0) ||
			(i == RIGHT_OPT && e->curs_pos < e->curs_max))
		move_cursor_word(e, i, str);
	else if (i == CUT_OPT | i == PASTE_OPT | i == COPY_OPT)
		copy_paste_mod(e, i, elem);
}
