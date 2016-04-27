/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:50:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/27 21:08:10 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_print_tab(char **array)
{
	int i;

	i = 0;
	if (!array || !array[i])
		return ;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}

char	**ft_tab_strcpy(char **to_copy)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	copy = NULL;
	if (!to_copy)
		return (NULL);
	while (to_copy[i])
		i++;
	copy = (char**)malloc(sizeof(*copy) * (i + 1));
	ft_bzero(copy, sizeof(*copy) * (i + 1));
	while (j < i)
	{
		copy[j] = ft_strdup(to_copy[j]);
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

void	clear_tab(char **array)
{
	int		i;

	i = 0;
	if (!array)
		return ;
	while (array[i] && array[i][0])
	{
		ft_strdel(&array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

char	**ft_tab_remove(char **array, int line)
{
	int		i;
	int		j;
	int		k;
	char	**copy;

	i = 0;
	j = 0;
	k = 0;
	while (array && array[i])
		i++;
	copy = (char**)malloc(sizeof(*copy) * (i + 1));
	ft_bzero(copy, sizeof(*copy) * (i));
	while (j < i)
	{
		if (j != line)
			copy[k++] = array[j];
		else
			ft_strdel(&(array[j]));
		j++;
	}
	free(array);
	array = NULL;
	copy[k] = NULL;
	return (copy);
}

char	**ft_tab_add(char **array, char *var)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	copy = NULL;
	while (array && array[i])
		i++;
	copy = (char**)malloc(sizeof(*copy) * (i + 2));
	ft_bzero(copy, sizeof(*copy) * (i + 2));
	while (j < i)
	{
		copy[j] = array[j];
		j++;
	}
	free(array);
	array = NULL;
	copy[j++] = var;
	copy[j] = NULL;
	return (copy);
}
