/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:12:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:12:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		juste_spac(char *str)
{
	int		i;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

static int		detect_parse_error(t_cmds **root)
{
	t_cmds *tmp;

	tmp = *root;
	while (tmp)
	{
		if ((juste_spac(tmp->cmd) == 1 || tmp->cmd == NULL) && tmp->pipe == 1)
		{
			ft_putstr("syntax error near unexpected token `|'\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static t_cmds	*exec_no_pipe(t_cmds *tmp, t_builtin *b)
{
	io_to_argv(tmp, 1);
	special_char(&tmp->cmd, b);
	init_builtin(b, tmp->cmd);
	if (!b->argv)
		return (NULL);
	clean_quote(b->argv);
	get_command(b->argv[0], b);
	if (b->path)
		do_fork(b, tmp);
	return (tmp->next);
}

void			parser(t_cmds **root, t_builtin *b)
{
	t_cmds	*tmp;

	if (detect_parse_error(root) == 1)
		return ;
	tmp = *root;
	while (tmp != NULL)
	{
		if (tmp->pipe == 0)
			tmp = exec_no_pipe(tmp, b);
		else if (tmp->pipe == 1)
			tmp = exec_pipe(tmp);
	}
}
