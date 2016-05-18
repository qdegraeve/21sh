/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:59 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/18 19:01:21 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, t_elem *alst, void (*del)(void *, size_t))
{
	if (del == NULL || alst == NULL)
		return ;
	if (lst->length > 1)
	{
		if (alst == lst->head)
		{
			lst->head = lst->head->next;
			lst->head->prev = NULL;
		}
		else if (alst == lst->tail)
		{
			lst->tail->prev->next = NULL;
			lst->tail = lst->tail->prev;
		}
		if (alst->prev != NULL)
			alst->prev->next = alst->next;
		if ((alst)->next != NULL)
			alst->next->prev = alst->prev;
	}
	else if (lst->length == 1)
	{
		lst->head = NULL;
		lst->tail = NULL;
		lst = NULL;
	}
	del((alst)->content, (alst)->content_size);
	free(alst);
	lst->length--;
	lst->length--;
	alst = NULL;
}
