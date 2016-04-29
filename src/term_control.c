/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 14:27:06 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/29 16:12:06 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_env(t_env *e)
{
	e->curs_pos = 0;
	e->curs_max = 0;
	e->length = 0;
	e->on = 0;
	e->line = 0;
	e->col = 0;
	e->up = 0;
	e->fd = 0;
}

void	term_set(void)
{
	char			*name;
	struct termios	term;

	if (!(name = getenv("TERM")))
	{
		ft_putendl_fd("ft_select cannot work within an empty environment", 2);
		exit(EXIT_FAILURE);
	}
	tgetent(NULL, name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

void	term_reset(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= (ECHO);
	term.c_lflag &= (ICANON);
	tcsetattr(0, TCSANOW, &term);
}

t_env	*get_env()
{
	static t_env	*e = NULL;

	if (!e)
		e = (t_env*)malloc(sizeof(t_env) + 1);
	return(e);
}

int		ft_putchar2(int c)
{
	ft_putchar_fd(c, get_env()->fd);
	return (0);
}

void	initial_position()
{
	tputs(tgetstr("rc", NULL), 0, ft_putchar2);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
}
