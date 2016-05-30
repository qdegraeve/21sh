/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:12:31 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:12:31 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	resize(int sig)
{
	t_history		*h;
	char			*str;
	struct winsize	win;
	t_env			*e;

	e = get_env();
	h = e->elem ? e->elem->content : NULL;
	if (h == NULL)
		return ;
	str = h->command_edit ? h->command_edit : h->command;
	if (sig == SIGWINCH)
	{
		go_to_position(e, str, 0);
		tputs(tgetstr("cd", NULL), 0, ft_putchar2);
		ioctl(0, TIOCGWINSZ, &win);
		e->width = win.ws_col;
		ft_putstr(str);
		tputs(tgetstr("sc", NULL), 0, ft_putchar2);
		go_to_position(e, str, e->curs_pos);
	}
}

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		if (get_env()->edit)
			prompt(1);
		else
			get_buil()->error = 1;
	}
}

void	signal_catcher(void)
{
	signal(SIGWINCH, resize);
	signal(SIGINT, ctrl_c);
}
