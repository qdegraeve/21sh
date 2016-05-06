/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:51 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/06 13:18:32 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list *lst, void (*del)(void *, size_t))
{
	t_elem *tmp;
	t_elem *backup;

	if (lst == NULL || del == NULL)
		return ;
	tmp = lst->head;
	while (lst->length-- > 0)
	{
		backup = tmp->next;
		ft_lstdelone(lst, &tmp, (*del));
		tmp = backup;
	}
	lst = NULL;
}
