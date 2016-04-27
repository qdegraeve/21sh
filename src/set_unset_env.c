/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:39:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/30 12:51:26 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_str(char a, char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != a)
			i++;
	}
	if (str[i] == a)
		return (i);
	else
		return (-1);
}

void	set_env_one(t_builtin *b, char *add, int j)
{
	int		i;

	i = 0;
	while (b->env && b->env[i])
	{
		if (ft_strncmp(b->env[i], add, j) == 0)
		{
			ft_strdel(&b->env[i]);
			b->env[i] = add;
			b->argv = ft_tab_remove(b->argv, 0);
			exec_setenv(b);
			return ;
		}
		i++;
	}
	b->env = ft_tab_add(b->env, add);
}

void	exec_setenv(t_builtin *b)
{
	char	*new;
	int		j;

	j = 0;
	new = NULL;
	while (b->argv[0] && (j = search_str('=', b->argv[0])) >= 0)
	{
		new = ft_strdup(b->argv[0]);
		set_env_one(b, new, j);
	}
}

void	unset_env_one(char *remove, t_builtin *b)
{
	int		j;

	j = 0;
	while (b->env && b->env[j])
	{
		if (ft_strncmp(remove, b->env[j], ft_strlen(remove)) == 0)
		{
			b->env = ft_tab_remove(b->env, j);
			break ;
		}
		j++;
	}
}

void	exec_unsetenv(t_builtin *b)
{
	int		i;

	i = 0;
	while (b->argv[i])
		i++;
	if (i < 1)
	{
		ft_putendl_fd("unsetenv: too few arguments", 2);
		b->error = 1;
		return ;
	}
	i = 0;
	while (b->argv[i])
	{
		unset_env_one(b->argv[i], b);
		i++;
	}
}
