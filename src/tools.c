/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:12:22 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:12:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		del_lst_char(void *content, size_t size)
{
	t_history	*h;

	h = content;
	if (h->command)
		ft_strdel(&h->command);
	if (h->command_edit)
		ft_strdel(&h->command_edit);
	ft_bzero(content, size);
	free(content);
	content = NULL;
}

void		list_init(t_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}

t_builtin	*get_buil(void)
{
	static t_builtin	*b = NULL;

	if (!b)
	{
		b = (t_builtin*)malloc(sizeof(t_builtin) + 1);
		ft_bzero(b, sizeof(t_builtin));
	}
	return (b);
}
