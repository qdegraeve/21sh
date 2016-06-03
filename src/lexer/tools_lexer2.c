#include "shell.h"

static void	del_io(t_io *delme)
{
	t_io	*freeme;

	while (delme)
	{
		free(delme->io);
		freeme = delme;
		delme = delme->next;
		free(freeme);
	}
}

void		del_lex_io(t_cmds **root)
{
	t_cmds *tmp;
	t_cmds *freeme;

	tmp = *root;
	while (tmp)
	{
		if (tmp->input)
		{
			del_io(tmp->input);
			free(tmp->tab_i);
		}
		if (tmp->output)
		{
			del_io(tmp->output);
			free(tmp->tab_o);
		}
		free(tmp->cmd);
		freeme = tmp;
		tmp = tmp->next;
		free(freeme);
	}
}

t_quote		*get_quote(void)
{
	static t_quote q;

	q.quote = 0;
	q.bquote = 0;
	q.bquote = 0;
	return (&q);
}

int			get_priority(char *str)
{
	int		priority;
	int		i;

	priority = 0;
	i = 0;
	while (str[i] && (priority = get_io(&str[i])) == 3)
		i++;
	return (priority);
}

char		*exeption(char *str)
{
	str++;
	return (NULL);
}
