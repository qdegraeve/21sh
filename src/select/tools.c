
#include "ft_select.h"

void	liste_init(t_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}

void	env_init_select(t_env_select *e)
{
	e->length = 0;
	e->up = 0;
	e->line = 0;
	e->on = 0;
	e->col = 0;
	e->fd = 0;
}

void	del_choice(void *c, size_t content_size)
{
	ft_strdel(&((t_choice*)c)->arg);
	ft_bzero(c, content_size);
	free(c);
}
