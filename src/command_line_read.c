/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 12:04:27 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/29 16:11:28 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		keys_action(t_env *e, int input, t_list *lst)
{
	static t_elem	*elem = NULL;
	t_history		h;
	t_history		*h1;
	
	if (!elem)
	{
		ft_bzero(&h, sizeof(t_history));
		ft_lstadd_last(lst, &h, sizeof(t_history));
		elem = lst->tail;
	}
	h1 = elem->content;
	if (input > 31 && input < 127)
		write_char(e, (char)input, elem);
	else if (input == 127 && e->curs_pos != 0)
		h1->command_edit = delete_char(e, h1->command_edit ? h1->command_edit : h1->command);
	else if (input == KLEFT && e->curs_pos)
	{
			e->curs_pos--;
			tputs(tgetstr("le", NULL), 0, ft_putchar2);
	}
	else if (input == KRIGHT && e->curs_pos < e->curs_max)
	{
			e->curs_pos++;
			tputs(tgetstr("nd", NULL), 0, ft_putchar2);
	}
	else if ((input == KUP && elem->prev) || (input == KDOWN && elem->next))
		elem = command_memory(e, input, lst, elem);
	else if (input == 10)
	{

		list_to_string(lst, elem);
		if (h1->command)
			elem = lst->tail->next;
	}
	return (0);
}

void	list_to_string(t_list *lst, t_elem *elem)
{
	t_history	*h;

	h = elem->content;
	if (h->command_edit)
		((t_history*)lst->tail->content)->command = ft_strdup(h->command_edit);
	ft_strdel(&h->command_edit);
	h->to_save = 1;
}

char	*get_input(t_builtin *b)
{
	int		input;
	char	buf[5];

	input = 0;
	ft_bzero(buf, 4);
	term_set();
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	while (42)
	{
		if (input == 10)
		{
			ft_putchar_fd('\n', get_env()->fd);
			term_reset();
			return (((t_history*)b->lst.tail->content)->command);
		}
		else
		{
			read(0, buf, 4);
			buf[4] = '\0';
			input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
			keys_action(get_env(), input, &b->lst);
			ft_bzero(buf, 4);
		}
		//		ft_printf("input == %d\n", input);
	}
}
