#include "shell.h"

void move_cursor_line(t_env *e, int input)
{
	int		diff;
	int		move;

	diff = e->curs_max;
	move = 0;
	if (input == HOME && e->curs_pos)
	{
		if ((move = (e->curs_pos + e->prompt_len) / e->width))
			tputs(tgoto(tgetstr("UP", NULL), 0, move), 0, ft_putchar2);
		move = ((e->curs_pos + e->prompt_len) % e->width) - e->prompt_len;
		tputs(tgoto(tgetstr("LE", NULL), 0, move), 0, ft_putchar2);
		tputs(tgetstr("sc", NULL), 0, ft_putchar2);
		e->curs_pos = 0;
	}
	else if (input == END && e->curs_max - e->curs_pos > 0)
	{
		move = (e->curs_pos + e->prompt_len) / e->width;
		if ((move = ((e->curs_max + e->prompt_len) / e->width) - move))
			tputs(tgoto(tgetstr("DO", NULL), 0, move), 0, ft_putchar2);
		move = ((e->curs_max + e->prompt_len) % e->width) - ((e->curs_pos + e->prompt_len) % e->width);
		tputs(tgoto(tgetstr("RI", NULL), 0, move), 0, ft_putchar2);
		e->curs_pos = e->curs_max;
	}
}

void move_cursor_word(t_env *e, int input)
{
	e = (void*)e;
	if (input == LEFT_OPT)
	{

	}
	else if (input == RIGHT_OPT)
	{

	}
}
