/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 10:05:20 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/29 12:02:49 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int j;

	i = ft_strlen(dest);
	j = 0;
	if (src)
	{
		while (src[j])
		{
			dest[i + j] = src[j];
			j++;
		}
		dest[i + j] = '\0';
	}
	return (dest);
}
