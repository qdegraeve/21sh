/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:40 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	do_fork(t_builtin *b, t_cmds *root)
{
	pid_t	parent;

	parent = fork();
	if (parent > 0)
		waitpid(parent, NULL, 0);
	else if (parent == -1)
		exit(EXIT_FAILURE);
	else if (parent == 0)
	{
		exec_simple(root, b);
		exit(EXIT_FAILURE);
	}
}
