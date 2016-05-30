/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:36 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 21:20:02 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_cmds(char *str, int pipe, t_cmds **root)
{
	t_cmds *tmp;
	t_cmds *new;

	new = *root;
	tmp = (t_cmds*)malloc(sizeof(t_cmds));
	ft_bzero(tmp, sizeof(t_cmds));
	tmp->cmd = str;
	tmp->pipe = pipe;
	if (!new)
		*root = tmp;
	else
	{
		while (new->next)
			new = new->next;
		new->next = tmp;
	}
}

void	add_io(char *str, t_cmds **root, int fd)
{
	t_io	*tmp;
	t_io	*new;
	t_cmds	*last;

	last = *root;
	while (last->next != NULL)
		last = last->next;
	new = fd == 1 ? last->input : last->output;
	tmp = (t_io*)malloc(sizeof(t_io));
	tmp->io = str;
	tmp->next = NULL;
	if (!new)
	{
		if (fd == 1)
			last->input = tmp;
		else
			last->output = tmp;
	}
	else
	{
		while (new->next)
			new = new->next;
		new->next = tmp;
	}
}

void	count(int *i, int *total, int counter)
{
	*i = *i + counter;
	*total = *total + counter;
}

int		get_io(char *str)
{
	if (str && str[0] == '|')
		return (2);
	else if (str && str[0] == ';')
		return (1);
	else if (str && str[0] == '>' && str[1] == '>')
		return (-3);
	else if (str && str[0] == '>')
		return (-4);
	else if (str && str[0] == '<' && str[1] == '<')
		return (-2);
	else if (str && str[0] == '<')
		return (-1);
	return (3);
}

int		space_priority(char *str)
{
	if (str && str[0] == '>' && str[1] == '>')
		return (2);
	else if (str && str[0] == '>')
		return (1);
	else if (str && str[0] == '<' && str[1] == '<')
		return (2);
	else if (str && str[0] == '<')
		return (1);
	return (0);
}
