#include "shell.h"

void		init_env(t_env *e, char *src)
{
	e->curs_pos = 0;
	e->curs_max = 0;
	e->fd = 0;
	e->pipe = 0;
	e->cmdand = 0;
	e->cmdor = 0;
	e->q.quote = 0;
	e->q.bquote = 0;
	e->q.dquote = 0;
	e->prompt_len = 0;
	e->width = 0;
	e->sel = 0;
	e->src = src;
	e->edit = 1;
	e->dyn = 0;
	e->cmd = 0;
	e->complete = NULL;
	e->choices = NULL;
}

void		term_set(void)
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

void		term_reset(void)
{
	tcsetattr(0, TCSANOW, &get_env()->term);
}

static void	init_tgetstr(t_env *e)
{
	e->up = tgetstr("UP", NULL);
	e->down = tgetstr("DO", NULL);
	e->ri = tgetstr("RI", NULL);
	e->le = tgetstr("LE", NULL);
	e->cd = tgetstr("cd", NULL);
	e->sc = tgetstr("sc", NULL);
	e->rc = tgetstr("rc", NULL);
	e->cr = tgetstr("cr", NULL);
	e->down_one = tgetstr("hd", NULL);
	e->up_one = tgetstr("up", NULL);
}

t_env		*get_env(void)
{
	static t_env	*e = NULL;
	char			*name;
	char			*temp;

	name = NULL;
	if (!e)
	{
		e = (t_env*)malloc(sizeof(t_env));
		ft_bzero(e, sizeof(t_env));
		if (!(name = ft_getenv("TERM", get_buil()->env)))
			exit(EXIT_FAILURE);
		tgetent(NULL, name);
		temp = tgetstr("pc", NULL);
		PC = temp ? *temp : 0;
		BC = tgetstr("le", NULL);
		UP = tgetstr("up", NULL);
		init_tgetstr(e);
		tcgetattr(0, &e->term);
	}
	return (e);
}
