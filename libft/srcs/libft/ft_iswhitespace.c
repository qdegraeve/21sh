/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 09:49:17 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 10:21:09 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iswhitespace(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
