#include "shell.h"

void move_cursor_line(t_env *e, int input)
{
	int		diff;
	int		move;

	diff = e->curs_max;
	move = 0;
	if (input == HOME && e->curs_pos)
	{
		tputs(tgoto(tgetstr("LE", NULL), 0, e->width), 0, ft_putchar2);
		if ((move = (e->curs_pos - 1 + e->prompt_len) / e->width))
			tputs(tgoto(tgetstr("UP", NULL), 0, move), 0, ft_putchar2);
		tputs(tgoto(tgetstr("RI", NULL), 0, e->prompt_len), 0, ft_putchar2);
		tputs(tgetstr("sc", NULL), 0, ft_putchar2);
		e->curs_pos = 0;
	}
	else if (input == END && e->curs_max - e->curs_pos > 0)
	{
		move = (e->curs_pos + e->prompt_len) / e->width;
		if ((move = ((e->curs_max + e->prompt_len) / e->width) - move))
			tputs(tgoto(tgetstr("DO", NULL), 0, move), 0, ft_putchar2);
		move = ((e->curs_max + e->curs_pos) % e->width);
		tputs(tgoto(tgetstr("RI", NULL), 0, move), 0, ft_putchar2);
		e->curs_pos = e->curs_max;
	}
}

void move_cursor_word(t_env *e, int input, char *str)
{
	int		save_pos;
	int		i;
	int		j;

	save_pos = e->curs_pos;
	i = 0;
	j = 0;
	if (input == LEFT_OPT)
	{
	}
	else if (input == RIGHT_OPT)
	{
		if (str[save_pos] == ' ')
			save_pos++;
		while (save_pos < e->curs_max)
		{
			if (str[save_pos] == ' ')
			{
				i++;
				break;
			}
			save_pos++;
			j++;
		}
		if (i > 0)
		{
			tputs(tgoto(tgetstr("RI", NULL), 0, j), 0, ft_putchar2);
			e->curs_pos += i;
		}
	}
}
