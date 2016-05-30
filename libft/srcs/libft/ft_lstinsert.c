/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 18:36:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/27 20:18:52 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstinsert(t_list *lst, void *content, int content_size, int pos)
{
	int		i;
	t_elem	*elem;
	t_elem	*new;

	elem = lst->head;
	i = 0;
	if (lst->length == 0 || pos == 0)
		ft_lstadd_first(lst, content, content_size);
	else if (pos == lst->length)
		ft_lstadd_last(lst, content, content_size);
	else
	{
		new = NULL;
		if (!(new = ft_lstnew(content, content_size)))
			return (-1);
		while (i++ < pos)
			elem = elem->next;
		new->next = elem;
		new->prev = elem->prev;
		elem->prev->next = new;
		elem->prev = new;
		lst->length++;
	}
	return (0);
}
