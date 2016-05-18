/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 12:29:07 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/18 16:11:49 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	del_lst_char(void *content, size_t size)
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

void	list_init(t_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}

t_builtin *get_buil()
{
	static t_builtin *b = NULL;

	if (!b)
		b = (t_builtin*)malloc(sizeof(t_builtin) + 1);
	return (b);
}
