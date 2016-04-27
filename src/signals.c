/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 14:40:44 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/27 19:50:56 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	end_select(int sig)
{
	DEBUG
	ft_printf("signal == %d\n", sig);
	if (sig != SIGWINCH && sig != SIGSTOP && sig != SIGCONT)
	{
		term_reset(get_env()->term);
		close(get_env()->fd);
		exit(0);
	}
}

//void	resize(int sig)
//{
//	if (sig == SIGWINCH)
//	{
//		display_choices(get_env());
//		signal(SIGWINCH, resize);
//	}
//}
//
void	suspend(int sig)
{
	char	away[2];

	if (sig == SIGTSTP)
	{
		term_reset(get_env()->term);
		signal(SIGTSTP, SIG_DFL);
		away[0] = get_env()->term.c_cc[VSUSP];
		away[1] = '\0';
		ioctl(0, TIOCSTI, away);
	}
}

void	restart(int sig)
{
	t_env	*e;

	e = get_env();
	if (sig == SIGCONT)
	{
		signal(SIGTSTP, suspend);
		term_set();
	}
}

void	signal_catcher(void)
{
	int i;

	i = 0;
//	signal(SIGWINCH, resize);
	signal(SIGTSTP, suspend);
	signal(SIGCONT, restart);
	while (i < 32)
	{
		if (i != SIGWINCH && i != SIGTSTP && i != SIGCONT)
			signal(i, end_select);
		i++;
	}
}
