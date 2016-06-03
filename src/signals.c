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
	t_env	*e;

	if (signal == SIGINT)
	{
		ft_putchar('\n');
		if (get_env()->edit)
		{
			e = get_env();
			ft_lstdelone(&get_buil()->lst, get_buil()->lst.tail, del_lst_char);
			e->elem = get_buil()->lst.tail->next;
			term_reset();
			init_env(e, NULL);
			prompt(1);
			term_set();
		}
		else
			get_buil()->error = 1;
	}
}

void	signal_catcher(void)
{
	signal(SIGWINCH, resize);
	signal(SIGINT, ctrl_c);
}
