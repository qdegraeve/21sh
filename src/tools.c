/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:50:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/30 16:20:07 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **tab)
{
	int i;

	i = 0;
	if (!tab || !tab[i])
		return ;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
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

void	clear_tab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] && tab[i][0])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

char	**ft_tab_remove(char **tab, int line)
{
	int		i;
	int		j;
	int		k;
	char	**copy;

	i = 0;
	j = 0;
	k = 0;
	while (tab && tab[i])
		i++;
	copy = (char**)malloc(sizeof(*copy) * (i + 1));
	ft_bzero(copy, sizeof(*copy) * (i));
	while (j < i)
	{
		if (j != line)
			copy[k++] = tab[j];
		else
			ft_strdel(&(tab[j]));
		j++;
	}
	free(tab);
	tab = NULL;
	copy[k] = NULL;
	return (copy);
}

char	**ft_tab_add(char **tab, char *var)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	copy = NULL;
	while (tab && tab[i])
		i++;
	copy = (char**)malloc(sizeof(*copy) * (i + 2));
	ft_bzero(copy, sizeof(*copy) * (i + 2));
	while (j < i)
	{
		copy[j] = tab[j];
		j++;
	}
	free(tab);
	tab = NULL;
	copy[j++] = var;
	copy[j] = NULL;
	return (copy);
}
