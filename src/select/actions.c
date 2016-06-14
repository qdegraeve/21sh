
#include "shell.h"

void	chose_one(t_env_select *e)
{
	int		i;
	t_elem	*elem;

	i = 0;
	elem = e->lst.head;
	while (i++ < e->on)
		elem = elem->next;
	((t_choice*)elem->content)->sel = (((t_choice*)elem->content)->sel + 1) % 2;
	e->on = (e->on + 1) % e->lst.length;
}

void	remove_one(t_env_select *e)
{
	int		i;
	t_elem	*elem;

	i = 0;
	elem = e->lst.head;
	while (i++ < e->on)
		elem = elem->next;
	ft_lstdelone(&e->lst, elem, del_choice);
	if (!e->lst.head)
	{
		term_reset_select(e->term);
		return ;
	}
}

int		selected(t_env_select *e, int input)
{
	int		i;
	int		j;
	t_elem	*elem;

	i = 0;
	j = 0;
	initial_position(e, get_env()->prompt_len);
	if (input == 10)
	{
		elem = e->lst.head;
		while (i < e->lst.length - 1)
		{
			if (((t_choice*)elem->content)->sel == 1)
			{
				get_env()->complete = triple_join(get_env()->complete, " ", ((t_choice*)elem->content)->arg, 1);
			}
			elem = elem->next;
			i++;
		}
	}
	term_reset_select(e->term);
	ft_lstdel(&e->lst, del_choice);
	return (1);
}
