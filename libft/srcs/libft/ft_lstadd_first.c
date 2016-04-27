/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:27:25 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/25 10:57:26 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_first(t_list *lst, void const *content, size_t cont_size)
{
	t_elem	*new;

	new = NULL;
	if (!(new = ft_lstnew(content, cont_size)))
		return (-1);
	if (lst->length == 0)
	{
		lst->tail = new;
		lst->head = new;
		lst->length++;
	}
	else
	{
		new->next = lst->head;
		lst->head->prev = new;
		lst->head = new;
		lst->length++;
	}
	return (0);
}
