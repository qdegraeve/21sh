/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 12:29:07 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/28 18:12:11 by qdegraev         ###   ########.fr       */
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
}

void	list_init(t_list *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
	lst->length = 0;
}
