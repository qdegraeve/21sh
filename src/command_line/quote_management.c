#include "shell.h"

int		ft_is_quote(char c)
{
	if (c == 34 || c == 39 || c == 96)
		return (1);
	return (0);
}

int		command_complete(t_quote *q, char *str)
{
	int		i;

	i = 0;
	q->quote = 0;
	q->bquote = 0;
	q->dquote = 0;
	while (str && str[i])
	{
		if (i == 0 || str[i - 1] != 92)
			ft_quote(q, str[i]);
		i++;
	}
	if (q->quote || q->bquote || q->dquote)
		return (0);
	return (1);
}

int		command_ncomplete(t_quote *q, char *str, int len)
{
	int		i;

	i = 0;
	q->quote = 0;
	q->bquote = 0;
	q->dquote = 0;
	while (str && i < len && str[i])
	{
		if (i == 0 || str[i - 1] != 92)
			ft_quote(q, str[i]);
		i++;
	}
	if (q->quote || q->bquote || q->dquote)
		return (0);
	return (1);
}

void	ft_quote(t_quote *q, char c)
{
	if (c == 39 && !q->dquote && !q->bquote)
		q->quote = (q->quote + 1) % 2;
	else if (c == 34 && !q->quote && !q->bquote)
		q->dquote = (q->dquote + 1) % 2;
	else if (c == 96 && !q->quote)
		q->bquote = (q->bquote + 1) % 2;
}

void	quote_prompt(t_env *e)
{
	e->prompt_len = 0;
	if (e->q.dquote || e->q.quote)
	{
		if (e->q.quote)
			ft_putstr("quote");
		else
			ft_putstr("dquote");
		e->prompt_len += e->q.dquote ? 6 : 5;
	}
	if (e->q.bquote || e->cmdand)
	{
		if (e->q.dquote)
			ft_putstr(" ");
		e->q.bquote ? ft_putstr("bquote") : ft_putstr("cmdand");
		e->prompt_len += e->q.dquote ? 7 : 6;
	}
	if (e->pipe || e->cmdor)
	{
		e->pipe ? ft_putstr("pipe") : ft_putstr("cmdor");
		e->prompt_len += e->pipe ? 4 : 5;
	}
	ft_putstr("> ");
	e->prompt_len += 2;
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
}
