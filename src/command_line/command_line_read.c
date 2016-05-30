/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:40 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			get_prev_lfeed(t_env *e, char *str, int i)
{
	int		lfeed;
	int		len;
	int		j;

	len = 0;
	lfeed = 0;
	j = 0;
	while (j < i)
	{
		if (str[j++] == '\n')
			lfeed++;
	}
	i--;
	while (str[i] && str[i] != '\n')
	{
		len++;
		i--;
	}
	if (lfeed)
		len = len % e->width;
	else
		len = (len + e->prompt_len) % e->width;
	return (len);
}

static int	pipe_end(t_env *e, char *str)
{
	int		len;

	len = ft_strlen(str) - 1;
	e->pipe = 0;
	if (!str)
		return (0);
	while (len > 0 && (str[len] == ' ' || str[len] == '\t' || str[len] == '\n'))
		len--;
	if (str[len] == '|')
	{
		e->pipe = 1;
		return (1);
	}
	return (0);
}

int			return_input(t_env *e, t_list *lst)
{
	t_history		*h;
	char			*str;
	int				cmp;

	cmp = 0;
	h = e->elem->content;
	str = NULL;
	str = ft_strlen(h->command_edit) > 0 ? h->command_edit : h->command;
	if (e->src != NULL && ((ft_strcmp(e->src, str)) != 0))
		cmp++;
	list_to_string(lst, &e->elem);
	h = e->elem->content;
	if (cmp || (e->src == NULL && (!command_complete(&e->q, h->command) ||
			(h->command && h->command[ft_strlen(h->command) - 1] == 92))) ||
			pipe_end(e, h->command) == 1)
	{
		h->command = ft_cjoin(h->command, ft_strdup("\n"));
		h->command_edit = ft_strnew(0);
		e->curs_pos = 0;
		e->curs_max = 0;
		return (1);
	}
	else if (ft_strlen(h->command) > 0)
		e->elem = lst->tail->next;
	return (0);
}

int			edit_line(t_env *e, int input, t_list *lst)
{
	t_history		*h;

	if (e->elem == NULL)
	{
		ft_lstadd_last(lst, &h, sizeof(t_history));
		e->elem = lst->tail;
		ft_bzero((t_history*)e->elem->content, sizeof(t_history));
	}
	if (input != 10)
		keys_actions(e, input, lst, &e->elem);
	else
		return (return_input(e, lst));
	return (0);
}

void		list_to_string(t_list *lst, t_elem **elem)
{
	t_history	*h;
	char		*str;

	str = ((t_history*)lst->tail->content)->command;
	h = (*elem)->content;
	if (h->command_edit)
	{
		if (*elem == lst->tail)
			((t_history*)lst->tail->content)->command =
				ft_cjoin(str, ft_strdup(h->command_edit));
		else
			((t_history*)lst->tail->content)->command =
				ft_strjoin(str, h->command_edit);
	}
	else if (*elem != lst->tail)
		((t_history*)lst->tail->content)->command = ft_strdup(h->command);
	if (h->command_edit)
		ft_strdel(&h->command_edit);
	h->command_edit = NULL;
	if (((t_history*)lst->tail->content)->command)
		h->to_save = 1;
	*elem = lst->tail;
}
