/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:59 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/27 20:39:59 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, t_elem **alst, void (*del)(void *, size_t))
{
	if (del == NULL || *alst == NULL)
		return ;
	if (lst->length > 1)
	{
		if (*alst == lst->head)
			lst->head = (*alst)->next;
		if (*alst == lst->tail)
			lst->tail = (*alst)->prev;
		if ((*alst)->prev != NULL)
			(*alst)->prev->next = (*alst)->next;
		if ((*alst)->next != NULL)
			(*alst)->next->prev = (*alst)->prev;
		lst->length--;
	}
	else if (lst->length == 1)
	{
		lst->head = NULL;
		lst->tail = NULL;
		lst->length--;
		lst = NULL;
	}
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
