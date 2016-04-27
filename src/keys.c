/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 15:00:25 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/27 20:46:32 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	del_char(void *content, size_t size)
{
	ft_bzero(content, size);
	free(content);
}

int		keys_action(t_env *e, int input, t_list *lst)
{
	t_elem	*elem;
	t_prompt p;
	int		i;

	elem = lst->head;
	i = 0;

	if (input > 31 && input < 127)
	{
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
	else if (input == 127 && e->curs_pos != 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_putchar2);
		tputs(tgetstr("dc", NULL), 0, ft_putchar2);
		e->curs_max--;
		while (++i < e->curs_pos)
			elem = elem->next;
		ft_lstdelone(lst, &elem, del_char);
		e->curs_pos--;
	}
	else if (input == KLEFT)
	{
		if (e->curs_pos)
		{
			e->curs_pos--;
			tputs(tgetstr("le", NULL), 0, ft_putchar2);
		}
	}
	else if (input == KRIGHT)
	{
		if (e->curs_pos < e->curs_max)
		{
			e->curs_pos++;
			tputs(tgetstr("nd", NULL), 0, ft_putchar2);
		}
	}
	return (0);
}

void	list_init(t_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}

char	*get_input(void)
{
	int		input;
	char	buf[5];
	t_list	lst;
	int	i;
	t_elem *elem = NULL;
	char	*tmp = NULL;

	i = 0;
	list_init(&lst);
	input = 0;
	ft_bzero(buf, 4);
	term_set();
	get_env()->fd = open(ttyname(STDIN_FILENO), O_RDWR);
	while (input != 10)
	{
		read(0, buf, 4);
		buf[4] = '\0';
		input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
		if (input == 10)
		{
			elem = lst.head;
			tmp = (char*)malloc(lst.length + 1);
			while (i < lst.length)
			{
				tmp[i++] = ((t_prompt*)elem->content)->letter;
				elem = elem->next;
			}
			tmp[i] = '\0';
			ft_putchar_fd('\n', get_env()->fd);
			close(get_env()->fd);
			term_reset(get_env()->term);
			return (tmp);
		}
		else
			keys_action(get_env(), input, &lst);
		ft_bzero(buf, 4);
	}
	return (NULL);
}
