#include "shell.h"

void		move_up(t_env *e, char *str)
{
	int		i;
	int		tmp;
	int		row;

	row = calc_row(e, str, e->curs_pos);
	i = 0;
	tmp = e->curs_pos - row - 2;
	if (calc_line(e, str, e->curs_pos, 0))
	{
		while (i < e->width && e->curs_pos > i)
		{
			if (str[tmp - i] == '\n')
				break ;
			i++;
		}
		if (i < row)
			i = row + 1;
		else
			i++;
		go_to_position(e, str, e->curs_pos - i);
		e->curs_pos -=  i;
	}
}

int			calc_rest_down(t_env *e, char *str, int pos, int row)
{
	int		i;

	i = 0;
	while (i < row && pos + i < e->curs_max && str[pos + i] != '\n')
		i++;
	return (i);
}

void		move_down(t_env *e, char *str)
{
	int		i;
	int		tmp;
	int		row;

	i = 0;
	row = calc_row(e, str, e->curs_pos);
	tmp = e->curs_pos;
	if (calc_line(e, str, e->curs_max, e->curs_pos - row))
	{
		while (i < e->width && tmp + i < e->curs_max)
		{
			if (str[tmp + i] == '\n')
				break ;
			i++;
		}
		if (i < e->width - row)
			i += calc_rest_down(e, str, tmp + i + 1, row) + 1;
		else
			i++;
		go_to_position(e, str, e->curs_pos + i);
		e->curs_pos +=  i;
	}
}
