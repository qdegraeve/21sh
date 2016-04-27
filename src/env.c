/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:46:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/30 16:30:54 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_options(t_builtin *b, char *av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 'u')
			b->env_u = 1;
		else if (av[i] == 'P')
			b->env_p = 1;
		else if (av[i] == 'i')
			b->env_i = 1;
		else if (av[i] == 'v')
			b->env_v = 1;
		i++;
	}
}

void	set_env_options(t_builtin *b)
{
	if (!b->env_i)
	{
		if (b->env_cpy)
			clear_tab(b->env_cpy);
		b->env_cpy = ft_tab_strcpy(b->env);
	}
	else
	{
		b->env_cpy = b->env;
		b->env = NULL;
	}
	if (b->env_u)
	{
		unset_env_one(b->argv[0], b);
		b->argv = ft_tab_remove(b->argv, 0);
	}
	else
		exec_setenv(b);
}

void	exec_env(t_builtin *b)
{
	int		i;

	i = 0;
	if (!b->argv[0])
	{
		ft_print_tab(b->env);
		return ;
	}
	while (b->argv[i] && b->argv[i][0] == '-')
	{
		env_options(b, b->argv[i]);
		b->argv = ft_tab_remove(b->argv, i);
	}
	set_env_options(b);
	if (b->argv[0])
		get_command(b->argv[0], b);
	else
		ft_print_tab(b->env);
}
