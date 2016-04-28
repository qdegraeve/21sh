/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_edit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 12:22:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/28 12:27:26 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	write_char(t_env *e, int input, t_list *lst)
{
	t_prompt p;

	p.letter = (char)input;
	if (e->curs_max != e->curs_pos)
		tputs(tgetstr("im", NULL), 0, ft_putchar2);
	ft_putchar_fd(input, e->fd);
	if (e->curs_max != e->curs_pos)
		tputs(tgetstr("ei", NULL), 0, ft_putchar2);
	ft_lstinsert(lst, &p, 1, e->curs_pos);
	e->curs_max++;
	e->curs_pos++;
}

void	delete_char(t_env *e, t_list *lst)
{
	t_elem	*elem;
	int		i;

	i = 0;
	elem = lst->head;
	tputs(tgetstr("le", NULL), 0, ft_putchar2);
	tputs(tgetstr("dc", NULL), 0, ft_putchar2);
	e->curs_max--;
	while (++i < e->curs_pos)
		elem = elem->next;
	ft_lstdelone(lst, &elem, del_lst_char);
	e->curs_pos--;
}
