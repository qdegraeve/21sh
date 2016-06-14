
#include "ft_select.h"

void			term_set_select()
{
	char			*name;
	struct winsize	win;
	t_env_select	*e;
	struct termios	term;

	e = get_env_select();
	name = ft_getenv("TERM", get_buil()->env);
	tgetent(NULL, name);
	tcgetattr(0, &e->term);
	term = e->term;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag |= (ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	ioctl(0, TIOCGWINSZ, &win);
	e->col = win.ws_col;
	tputs(tgetstr("vi", NULL), 0, ft_putchar2);
}

void			term_reset_select(struct termios term)
{
	tputs(tgetstr("ve", NULL), 1, ft_putchar2);
	tcsetattr(0, TCSANOW, &term);
}

t_env_select	*argv_copy(char **av, int ac)
{
	t_env_select	*e;
	t_choice		c;
	int				i;

	i = 1;
	e = NULL;
	c.sel = 0;
	e = get_env_select();
	env_init_select(e);
	liste_init(&e->lst);
	while (i < ac)
	{
		c.sel = 0;
		c.arg = NULL;
		if ((size_t)e->length < ft_strlen(av[i]))
			e->length = ft_strlen(av[i]);
		c.arg = ft_strdup(av[i]);
		ft_lstadd_last_circ(&e->lst, &c, sizeof(c));
		i++;
	}
	term_set_select();
	return (e);
}

int			ask_for_select(t_env_select *e, int i)
{
	char	buf[2];

	ft_bzero(buf, 2);
	e->line_nbr = (i / (e->col / e->length));
	if (i % (e->col / e->length) != 0)
		e->line_nbr++;
	ft_putstr("21sh: do you wish to see all ");
	ft_putnbr(i);
	ft_putstr(" possibilities (");
	ft_putnbr(e->line_nbr);
	ft_putstr(" lines)?");
	read(0, buf, 1);
	buf[1] = '\0';
	if (buf[0] == 'y' || buf[0] == 'Y')
		return (0);
	return(1);
}

int			ft_select(char **list)
{
	t_env_select	*e;
	int				i;
	int				too_much;

	i = 0;
	too_much = 0;
	while (list && list[i])
		i++;
	e = argv_copy(list, i);
	if (i > 20)
		too_much = ask_for_select(e, i);
	if (!too_much)
	{
		signal_catcher_select();
		get_input_select(e);
	}
	else
		selected(e, 0);
	return (0);
}
