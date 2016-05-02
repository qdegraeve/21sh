#include "shell.h"

void move_cursor_line(t_env *e, int input)
{
	int		diff;

	diff = e->curs_max;
	if (input == HOME)
	{
			tputs(tgetstr("rc", NULL), 0, ft_putchar2);
			tputs(tgetstr("sc", NULL), 0, ft_putchar2);
			e->curs_pos = 0;
	}
	else if (input == END && e->curs_max - e->curs_pos > 0)
	{
			tputs(tgoto(tgetstr("RI", NULL), 0, e->curs_max -e->curs_pos), 0, ft_putchar2);
			e->curs_pos = e->curs_max;
	}
}

void move_cursor_word(t_env *e, int input)
{
	if (input == LEFT_OPT)
	{

	}
	else if (input == RIGHT_OPT)
	{

	}
}
