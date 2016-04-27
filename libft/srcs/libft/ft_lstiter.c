/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:00:09 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/20 15:20:26 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_elem *lst, void (*f)(t_elem *elem))
{
	t_elem	*backup;

	if (lst == NULL || f == NULL)
		return ;
	while (lst)
	{
		backup = lst->next;
		f(lst);
		lst = backup;
	}
}
