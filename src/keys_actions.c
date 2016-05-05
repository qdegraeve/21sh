#include "shell.h"

int		calc_row(t_env *e, char *str, int pos)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	ret = 0;
	while (i < pos && str[i] != '\n')
		i++;
	ret += (i + e->prompt_len - 1) % e->width;
	while (i <= pos)
	{
		j = 0;
		if (str[i] == '\n')
		{
			i++;
			ret = 0;
		}
		while (str[i] != '\n' && i++ <= pos)
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
	while (i < pos && str[i] != '\n')
		i++;
	ret += (i - 1 + e->prompt_len) / e->width;
	while (i < pos)
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
		tputs(tgoto(tgetstr("UP", NULL), 0, move), 0, ft_putchar2);
	if (!position)
		tputs(tgoto(tgetstr("RI", NULL), 0, e->prompt_len), 0, ft_putchar2);
	if (position && (move = calc_line(e, str, position)))
		tputs(tgoto(tgetstr("DO", NULL), 0, move), 0, ft_putchar2);
	if (position && (move = calc_row(e, str, position)))
		tputs(tgoto(tgetstr("RI", NULL), 0, move), 0, ft_putchar2);
}

void	keys_actions(t_env *e, int input, t_list *lst, t_elem **elem)
{
	t_history		*h;
	char			*str;

	h = (*elem)->content;
	str = ft_strlen(h->command_edit) > 0 ? h->command_edit : h->command;
	if (input > 31 && input < 127)
		write_char(e, (char)input, *elem);
	else if (input == 127 && e->curs_pos != 0)
	{
		if (!h->command_edit)
			h->command_edit = ft_strdup(h->command);
		h->command_edit = delete_char(e, h->command_edit);
	}
	else if (input == 4 && *elem == lst->tail)
	{
		if (!h->command_edit)
			exec_exit(get_buil());
	}
	else if (input == KLEFT && e->curs_pos)
	{
		go_to_position(e, str, e->curs_pos - 1);
		e->curs_pos--;
	}
	else if (input == KRIGHT && e->curs_pos < e->curs_max)
	{
		go_to_position(e, str, e->curs_pos + 1);
		e->curs_pos++;
	}
	else if ((input == KUP && (*elem)->prev) || (input == KDOWN && (*elem)->next))
		*elem = command_memory(e, input, lst, *elem);
	else if (input == END || input == HOME)
		move_cursor_line(e, input, str);
	else if ((input == LEFT_OPT  && e->curs_pos > 0) || (input == RIGHT_OPT && e->curs_pos < e->curs_max))
		move_cursor_word(e, input, str);
	else if (input == CUT_OPT | input == PASTE_OPT | input == COPY_OPT)
		copy_paste_mod(e, input, str, elem);
}
