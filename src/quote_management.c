#include "shell.h"

int		ft_is_quote(char c)
{
	if (c == 34 || (c > 38 && c < 42) || c == 96)
		return (1);
	return (0);
}

int		command_complete(t_env *e)
{
	if (e->quote || e->bquote || e->dquote || e->par)
		return (0);
	return (1);
}

void	ft_quote(t_env *e, char c)
{
//	ft_printf("km == %d\n", tgetflag("km"));
//	ft_printf("ws == %d\n", tgetnum("ws"));
//	ft_printf("li == %d\n", tgetnum("li"));
//	ft_printf("lm == %d\n", tgetnum("lm"));
//	ft_printf("ho == %s\n", tgetstr("ho", NULL));
//	ft_printf("mm == %s\n", tgetstr("mm", NULL));
	if (c == 39 && !e->dquote && !e->bquote)
		e->quote = (e->quote + 1) % 2;
	else if (c == 34 && !e->quote && !e->bquote)
		e->dquote = (e->dquote + 1) % 2;
	else if (c == 96 && !e->quote)
		e->bquote = (e->bquote + 1) % 2;
	else
	{
		if (c == 40)
			e->par++;
		if (c == 41)
			e->par--;
	}
}

void	quote_prompt(t_env *e)
{
	e->prompt_len = 0;
	if (e->dquote)
	{
		ft_putstr_fd("dquote", e->fd);
		e->prompt_len += 6;
	}
	if (e->quote)
	{
		ft_putstr_fd("quote", e->fd);
		e->prompt_len += 5;
	}
	if (e->bquote)
	{
		if (e->dquote)
			ft_putstr_fd(" ", e->fd);
		ft_putstr_fd("bquote", e->fd);
		e->prompt_len += e->dquote ? 7 : 6;
	}
	ft_putstr_fd("> ", e->fd);
	e->prompt_len += 2;
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
}
