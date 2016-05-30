/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:31 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:31 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	close_child_fd(t_cmds *root, int i, int nb, int fdes[][2])
{
	if (i != 0)
	{
		close(fdes[i - 1][1]);
		dup2(fdes[i - 1][0], STDIN_FILENO);
	}
	if (i != nb - 1)
	{
		close(fdes[i][0]);
		dup2(fdes[i][1], STDOUT_FILENO);
	}
	pipe_handler(root, get_buil());
	exec_simple(root, get_buil());
}
