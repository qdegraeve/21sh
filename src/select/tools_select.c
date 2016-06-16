
#include "ft_select.h"

void	liste_init(t_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}

void	env_init_select(t_env_select *e, char cmd)
{
	e->length = 0;
	e->up = 0;
	e->line = 0;
	e->on = 0;
	e->col = 0;
	e->row = 0;
	e->fd = 0;
	e->line_nbr = 0;
	e->yes = 0;
	e->cmd = cmd;
}

void	del_choice(void *c, size_t content_size)
{
	t_choice	*choice;

	choice = c;
	if (choice->arg)
		ft_strdel(&choice->arg);
	ft_bzero(c, content_size);
	free(c);
	c = NULL;
}
