#include "shell.h"

void	end_select(int sig)
{
	DEBUG
	ft_printf("signal == %d\n", sig);
	if (sig != SIGWINCH && sig != SIGSTOP && sig != SIGCONT)
	{
		term_reset();
		exit(0);
	}
}

void	resize(int sig)
{
	t_history		*h;
	char			*str;
	struct winsize	win;
	
	h = get_env()->elem ? get_env()->elem->content : NULL;
	if (h == NULL)
		return ;
	str = h->command_edit ? h->command_edit : h->command;
	if (sig == SIGWINCH)
	{
		ioctl(0, TIOCGWINSZ, &win);
		get_env()->width = win.ws_col;
		go_to_position(get_env(), str, 0);
		tputs(tgetstr("cd", NULL), 0, ft_putchar2);
		ft_putstr(str);
		tputs(tgetstr("sc", NULL), 0, ft_putchar2);
		go_to_position(get_env(), str, get_env()->curs_pos);
	}
}

void	suspend(int sig)
{
	char	away[2];

	if (sig == SIGTSTP)
	{
		term_reset();
		signal(SIGTSTP, SIG_DFL);
		away[0] = get_env()->term->c_cc[VSUSP];
		away[1] = '\0';
		ioctl(0, TIOCSTI, away);
	}
}

void	restart(int sig)
{
	t_env	*e;

	e = get_env();
	if (sig == SIGCONT)
		term_set();
}

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		prompt(1);
	}
}

void	signal_catcher(void)
{
//	int i;

//	i = 0;
	signal(SIGWINCH, resize);
	signal(SIGINT, ctrl_c);
//	signal(SIGTSTP, suspend);
//	signal(SIGCONT, restart);
//	while (i < 32)
//	{
//		if (i != SIGWINCH && i != SIGTSTP && i != SIGCONT)
//			signal(i, end_select);
//		i++;
//	}
}
