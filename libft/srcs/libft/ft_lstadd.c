/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:59:27 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/02 14:24:34 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_elem **alst, t_elem *to_add)
{
	if (alst == NULL || to_add == NULL)
		return ;
	to_add->next = *alst;
	*alst = to_add;
}
