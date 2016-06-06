/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_tty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 12:10:49 by qdegraev          #+#    #+#             */
/*   Updated: 2016/06/06 12:25:34 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		no_tty(t_builtin *b)
{
	char	*line;
	t_cmds	*root;
	int		i;

	i = 0;
	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		root = NULL;
		root = lexer(line);
		if (root)
			parser(&root, b);
		if (line)
			ft_strdel(&line);
		if (root)
			del_lex_io(&root);
		i++;
	}
	exec_exit(b);
}
