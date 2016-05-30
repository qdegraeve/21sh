/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:12:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:12:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	exit_error(t_builtin *b)
{
	b->error = 1;
	exit(EXIT_FAILURE);
}

void	exec_simple(t_cmds *root, t_builtin *b)
{
	if (root->tab_i != NULL)
	{
		if (get_priority(root->tab_i[0]) == -2 && doc(root->tab_i, b) == 1)
			exit_error(b);
		else if (get_priority(root->tab_i[0]) == -1 && rfile(root->tab_i) == 1)
			exit_error(b);
	}
	else if (root->tab_o != NULL)
	{
		if (get_priority(root->tab_o[0]) == -4 && wfile(root->tab_o) == 1)
			exit_error(b);
		else if (get_priority(root->tab_o[0]) == -3 && ape(root->tab_o) == 1)
			exit_error(b);
	}
	if (b->path)
		execve(b->path, b->argv, b->env);
	exit_error(b);
}
