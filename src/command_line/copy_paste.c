/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:38 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:38 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	cut(t_env *e, char **str, t_builtin *b)
{
	char	*dest;

	dest = NULL;
	if (b->paste)
		ft_strdel(&b->paste);
	if (ft_strlen(*str) > 0 && e->curs_pos < e->curs_max)
	{
		dest = ft_strnew(e->curs_pos);
		b->paste = ft_strdup(*str + e->curs_pos);
		go_to_position(e, *str, 0);
		dest = ft_strncat(dest, *str, e->curs_pos);
		ft_strdel(&*str);
		*str = dest;
		e->curs_max = e->curs_pos;
		tputs(tgetstr("cd", NULL), 0, ft_putchar2);
		ft_putstr(*str);
	}
}

static void	copy(t_env *e, char *str, t_builtin *b)
{
	if (b->paste)
		ft_strdel(&b->paste);
	if (ft_strlen(str) > 0 && e->curs_pos < e->curs_max)
		b->paste = ft_strdup(str + e->curs_pos);
}

static void	paste(t_env *e, char **str, t_builtin *b)
{
	char	*dest;
	int		i;

	i = 0;
	if (!b->paste)
		return ;
	go_to_position(e, *str, 0);
	e->curs_max = ft_strlen(*str) + ft_strlen(b->paste);
	dest = ft_strnew(e->curs_max);
	dest = ft_strncpy(dest, *str, e->curs_pos);
	dest = ft_strcat(dest, b->paste);
	if (e->curs_pos < e->curs_max)
		dest = ft_strcat(dest, *str + e->curs_pos);
	ft_strdel(str);
	*str = dest;
	dest[e->curs_max] = '\0';
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	ft_putstr(*str);
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	e->curs_pos += ft_strlen(b->paste);
	go_to_position(e, *str, e->curs_pos);
}

void		copy_paste_mod(t_env *e, int input, t_elem **elem)
{
	t_history	*h;

	h = (*elem)->content;
	if (input == COPY_OPT && !h->command_edit)
		copy(e, h->command, get_buil());
	else
	{
		if (!h->command_edit)
			h->command_edit = ft_strdup(h->command);
		if (input == CUT_OPT)
			cut(e, &h->command_edit, get_buil());
		else if (input == COPY_OPT)
			copy(e, h->command_edit, get_buil());
		else if (input == PASTE_OPT)
			paste(e, &h->command_edit, get_buil());
	}
}
