/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 15:00:25 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/28 12:29:46 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		keys_action(t_env *e, int input, t_list *lst)
{
	if (input > 31 && input < 127)
		write_char(e, input, lst);
	else if (input == 127 && e->curs_pos != 0)
		delete_char(e, lst);
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
	return (0);
}

void	list_to_string(char **line, t_list lst)
{
	t_elem *elem = NULL;
	int	i;

	i = 0;
	elem = lst.head;
	*line = (char*)malloc(lst.length + 1);
	while (i < lst.length)
	{
		(*line)[i++] = ((t_prompt*)elem->content)->letter;
		elem = elem->next;
	}
	(*line)[i] = '\0';
	ft_lstdel(&lst, del_lst_char);
}

void	get_input(char **line)
{
	int		input;
	char	buf[5];
	t_list	lst;

	list_init(&lst);
	input = 0;
	ft_bzero(buf, 4);
	term_set();
	*line = NULL;
	while (42)
	{
		read(0, buf, 4);
		buf[4] = '\0';
		input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
//		ft_printf("input == %d\n", input);
		if (input == 10)
		{
			list_to_string(line, lst);
			ft_putchar_fd('\n', get_env()->fd);
			term_reset(get_env()->term);
			return ;
		}
		else
			keys_action(get_env(), input, &lst);
		ft_bzero(buf, 4);
	}
}
