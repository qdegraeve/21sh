#include "shell.h"

void		chose_one(t_env_select *e)
{
	int		i;
	t_elem	*elem;

	i = 0;
	elem = e->lst.head;
	while (i++ < e->on)
		elem = elem->next;
	((t_choice*)elem->content)->sel = (((t_choice*)elem->content)->sel + 1) % 2;
	e->on = (e->on + 1) % e->lst.length;
	e->yes += ((t_choice*)elem->content)->sel ? 1 : -1;
}

void		remove_one(t_env_select *e)
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

static int	selected2(t_env_select *e, t_elem *elem, t_env *env, int i)
{
	t_choice	*c;

	c = elem->content;
	if (!e->cmd && c->sel == 1)
	{
		if (env->complete)
			env->complete = triple_join(env->complete, " ", c->arg, 1);
		else
			env->complete = ft_strdup(c->arg);
		return (1);
	}
	else if ((!e->yes || e->cmd) && i == e->on)
	{
		env->complete = ft_strdup(c->arg);
		return (1);
	}
	return (0);
}

int			selected(t_env_select *e, int input)
{
	int		i;
	int		del;
	t_elem	*elem;
	t_env	*env;

	i = 0;
	del = 0;
	env = get_env();
	if (input == 10)
	{
		elem = e->lst.head;
		while (i < e->lst.length)
		{
			del += selected2(e, elem, env, i);
			elem = elem->next;
			i++;
		}
	}
	initial_position(e, env->prompt_len, del);
	ft_lstdel(&e->lst, del_choice);
	term_reset_select(e->term);
	return (1);
}
