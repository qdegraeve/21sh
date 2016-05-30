/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:33 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:33 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_cmds	*send_cmds(t_cmds *tmp, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

static int		count_piped_cmd(t_cmds *tmp)
{
	int		i;

	i = 0;
	while (tmp && tmp->pipe == 1)
	{
		i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

int				pipe_handler(t_cmds *tmp, t_builtin *b)
{
	special_char(&tmp->cmd, b);
	init_builtin(b, tmp->cmd);
	clean_quote(b->argv);
	get_command(b->argv[0], b);
	if (b->path)
		return (1);
	return (0);
}

static void		pipe_manager(t_cmds *root, int nb)
{
	int		i;
	int		fdes[nb][2];
	pid_t	parent;

	i = 0;
	while (i < nb - 1)
		pipe(fdes[i++]);
	i = -1;
	while (++i < nb)
	{
		if ((parent = fork()) == -1)
			exec_exit(get_buil());
		if (parent == 0)
			close_child_fd(root, i, nb, fdes);
		else if (parent)
		{
			signal(SIGCHLD, SIG_IGN);
			if (i != 0)
				close(fdes[i - 1][0]);
			if (i != nb - 1)
				close(fdes[i][1]);
			root = root->next;
		}
	}
	waitpid(parent, NULL, 0);
}

t_cmds			*exec_pipe(t_cmds *tmp)
{
	int			nbcmd;

	if ((nbcmd = count_piped_cmd(tmp)) > 1000)
		ft_putendl_fd("21sh: fork: Resource temporarily unavailable", 2);
	else
	{
		io_to_argv(tmp, nbcmd);
		pipe_manager(tmp, nbcmd);
	}
	return (send_cmds(tmp, nbcmd));
}
