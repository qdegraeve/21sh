/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:59 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/20 11:08:11 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	more_than_one(t_list *lst, t_elem *alst)
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
	lst->length--;
}

void		ft_lstdelone(t_list *lst, t_elem *alst, void (*del)(void *, size_t))
{
	if (del == NULL || alst == NULL)
		return ;
	if (lst->length > 1)
		more_than_one(lst, alst);
	else if (lst->length == 1)
	{
		lst->head = NULL;
		lst->tail = NULL;
		lst->length--;
		lst = NULL;
	}
	del((alst)->content, (alst)->content_size);
	free(alst);
	alst = NULL;
}
