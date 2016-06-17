#include "shell.h"

void		move_up(t_env *e, char *str)
{
	int		tmp;
	int		row;
	int		row2;

	row = calc_row(e, str, e->curs_pos);
	row2 = 0;
	tmp = e->curs_pos - row - 1;
	if (calc_line(e, str, e->curs_pos, 0))
	{
		row2 = calc_row(e, str, tmp);
		if (row2 > row)
			tmp -= (row2 - row);
		go_to_position(e, str, tmp);
		e->curs_pos = tmp;
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
	if (e->curs_max > e->curs_pos && calc_line(e, str, e->curs_max, e->curs_pos - row + 1))
	{
		while (i < e->width && tmp + i < e->curs_max)
		{
			if (str[tmp + i] == '\n')
				break ;
			i++;
		}
		if (i < e->width - row)
			i += calc_rest_down(e, str, tmp + i + 1, row) + 1;
		if (i)
			go_to_position(e, str, e->curs_pos + i);
		e->curs_pos +=  i;
	}
}
