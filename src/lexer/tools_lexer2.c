/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:36 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:38:11 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	del_io(t_io *delme)
{
	t_io	*freeme;

	while (delme)
	{
		free(delme->io);
		freeme = delme;
		delme = delme->next;
		free(freeme);
	}
}

void		del_lex_io(t_cmds **root)
{
	t_cmds *tmp;
	t_cmds *freeme;

	tmp = *root;
	while (tmp)
	{
		if (tmp->input)
		{
			del_io(tmp->input);
			free(tmp->tab_i);
		}
		if (tmp->output)
		{
			del_io(tmp->output);
			free(tmp->tab_o);
		}
		free(tmp->cmd);
		freeme = tmp;
		tmp = tmp->next;
		free(freeme);
	}
}

t_quote		*get_quote(void)
{
	static t_quote q;

	q.quote = 0;
	q.bquote = 0;
	q.bquote = 0;
	return (&q);
}

int			get_priority(char *str)
{
	int		priority;
	int		i;

	priority = 0;
	i = 0;
	while (str[i] && (priority = get_io(&str[i])) == 3)
		i++;
	return (priority);
}
