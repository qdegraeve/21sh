/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:51 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/18 20:22:35 by qdegraev         ###   ########.fr       */
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
		ft_putendl("test1");
		backup = tmp->next;
		ft_lstdelone(lst, tmp, (*del));
		ft_putendl("test2");
		tmp = backup;
	}
	lst = NULL;
}
