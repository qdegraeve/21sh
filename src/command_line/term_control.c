/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:12:28 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:12:28 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_env(t_env *e, char *src)
{
	e->curs_pos = 0;
	e->curs_max = 0;
	e->length = 0;
	e->on = 0;
	e->line = 0;
	e->col = 0;
	e->up = 0;
	e->fd = 0;
	e->q.quote = 0;
	e->q.bquote = 0;
	e->q.dquote = 0;
	e->prompt_len = 0;
	e->width = 0;
	e->src = src;
	e->edit = 1;
}

void	term_set(void)
{
	struct winsize	win;
	t_env			*e;
	struct termios	term;

	e = get_env();
	term = e->term;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag |= (ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	ioctl(0, TIOCGWINSZ, &win);
	get_env()->width = win.ws_col;
}

void	term_reset(void)
{
	tcsetattr(0, TCSANOW, &get_env()->term);
}

t_env	*get_env(void)
{
	static t_env	*e = NULL;
	char			*name;

	name = NULL;
	if (!e)
	{
		e = (t_env*)malloc(sizeof(t_env));
		ft_bzero(e, sizeof(t_env));
		if (!(name = ft_getenv("TERM", get_buil()->env)))
			exit(EXIT_FAILURE);
		tgetent(NULL, name);
		tcgetattr(0, &e->term);
	}
	return (e);
}

int		ft_putchar2(int c)
{
	ft_putchar_fd(c, get_env()->fd);
	return (0);
}
