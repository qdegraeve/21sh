/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 14:40:56 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/01 15:18:54 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_fork(t_builtin *b)
{
	pid_t	parent;

	parent = fork();
	if (parent > 0)
		wait(NULL);
	else if (parent == -1)
		exit(EXIT_FAILURE);
	else if (parent == 0)
	{
		if (execve(b->path, b->argv, b->env) == -1)
			b->error = 1;
		b->error = 1;
		exit(EXIT_FAILURE);
	}
}
