#include "shell.h"

void		move_cursor_line(t_env *e, int input, char *str)
{
	int		diff;
	int		move;

	diff = e->curs_max;
	move = 0;
	if (input == HOME && e->curs_pos)
	{
		go_to_position(e, str, 0);
		e->curs_pos = 0;
	}
	else if (input == END && e->curs_max - e->curs_pos > 0)
	{
		tputs(e->rc, 0, ft_putchar2);
		tputs(e->sc, 0, ft_putchar2);
		e->curs_pos = e->curs_max;
	}
}

static void	move_cursor_word_right(t_env *e, char *str)
{
	int		j;
	int		blank;
	int		move;

	move = 0;
	j = 0;
	blank = ft_iswhitespace(str[e->curs_pos]);
	while (e->curs_pos <= e->curs_max)
	{
		if (ft_iswhitespace(str[e->curs_pos]) != blank ||
				e->curs_pos == e->curs_max)
		{
			if ((move = calc_line(e, str, e->curs_pos)))
				tputs(tgoto(e->down, 0, move), 0, ft_putchar2);
			if ((move = calc_row(e, str, e->curs_pos)))
			{
				tputs(tgoto(e->ri, 0, move - e->prompt_len), 0,
						ft_putchar2);
			}
			break ;
		}
		e->curs_pos++;
		j++;
	}
}

static void	move_cursor_word_left(t_env *e, char *str)
{
	int		j;
	int		blank;
	int		move;

	move = 0;
	j = 0;
	e->curs_pos--;
	blank = ft_iswhitespace(str[e->curs_pos]);
	while (e->curs_pos >= 0)
	{
		if (ft_iswhitespace(str[e->curs_pos]) != blank || e->curs_pos == 0)
		{
			if (e->curs_pos != 0)
				e->curs_pos++;
			if ((move = calc_line(e, str, e->curs_pos)))
				tputs(tgoto(e->down, 0, move), 0, ft_putchar2);
			if ((move = calc_row(e, str, e->curs_pos)))
				tputs(tgoto(e->ri, 0, move), 0, ft_putchar2);
			go_to_position(e, str, e->curs_pos);
			break ;
		}
		e->curs_pos--;
		j++;
	}
}

void		move_cursor_word(t_env *e, int input, char *str)
{
	go_to_position(e, str, 0);
	if (input == LEFT_OPT)
		move_cursor_word_left(e, str);
	else if (input == RIGHT_OPT)
		move_cursor_word_right(e, str);
}
