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
	if (c == 39)
		e->quote = (e->quote + 1) % 2;
	else if (c == 34)
		e->dquote = (e->dquote + 1) % 2;
	else if (c == 96)
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
	if (e->quote)
		ft_putstr_fd("quote> ", e->fd);
	else if (e->bquote)
		ft_putstr_fd("bquote> ", e->fd);
	else if (e->dquote)
		ft_putstr_fd("dquote> ", e->fd);
	else if (e->par > 0)
		ft_putstr_fd("> ", e->fd);
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
}
