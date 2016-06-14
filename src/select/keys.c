
#include "ft_select.h"

int		keys_action_select(t_env_select *e, int input)
{
	if (input == KUP)
		e->on = (e->on + e->lst.length - 1) % e->lst.length;
	else if (input == KDOWN)
		e->on = (e->on + 1) % e->lst.length;
	else if (input == KLEFT)
		e->on = (e->on + e->lst.length - e->line) % e->lst.length;
	else if (input == KRIGHT || input == TAB)
		e->on = (e->on + e->line) % e->lst.length;
	else if (input == 32 && !e->cmd)
		chose_one(e);
	else if (input == ESC || input == 10 || (input > 32 && input < 127))
	{
		selected(e, input);
		return (1);
	}
	return (0);
}

void	get_fd(t_env_select *e)
{
	int		fd = 0;

	e->fd = fd;
}

void	get_input_select(t_env_select *e)
{
	int		input;
	char	buf[5];
	int		ret;

	input = 0;
	while (input++ < e->line_nbr)
		ft_putchar('\n');
	input = 0;
	if (e->line_nbr)
		tputs(tgoto(get_env()->up, 0, (e->line_nbr)), 0, ft_putchar2);
	display_choices(e);
	ft_bzero(buf, 4);
	while (42)
	{
		read(0, buf, 4);
		buf[4] = '\0';
		input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
		if ((ret = keys_action_select(e, input)) == 0)
			display_choices(e);
		else
			return ;
		ft_bzero(buf, 4);
	}
}
