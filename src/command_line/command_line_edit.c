/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line_edit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:37 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:37 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*string_insert(t_env *e, char *src, char ins, int pos)
{
	char		*dest;
	char		letter[2];
	int			len;

	go_to_position(e, src, 0);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	letter[0] = ins;
	letter[1] = '\0';
	len = ft_strlen(src);
	dest = ft_strnew(len + 1);
	dest = ft_strncpy(dest, src, pos);
	dest = ft_strcat(dest, letter);
	if (pos < len)
		dest = ft_strcat(dest, src + pos);
	dest[len + 1] = '\0';
	if (src)
		ft_strdel(&src);
	return (dest);
}

static char	*delete_char(t_env *e, int input, char *src)
{
	char		*dest;
	int			len;

	go_to_position(e, src, 0);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	dest = NULL;
	len = ft_strlen(src) - 1;
	dest = ft_strnew(len);
	dest = ft_strncpy(dest, src, input == 127 ? e->curs_pos - 1 : e->curs_pos);
	dest = ft_strcat(dest, input == 127 ? src + e->curs_pos :
			src + e->curs_pos + 1);
	dest[len] = '\0';
	if (src)
		ft_strdel(&src);
	return (dest);
}

static void	display_command(t_env *e, int input, char *str)
{
	int			j;

	j = 0;
	e->curs_max = ft_strlen(str);
	ft_putstr(str);
	if ((e->prompt_len + e->curs_max) % e->width == 0)
		tputs(tgetstr("do", NULL), 0, ft_putchar2);
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	if (input == 127)
		j = e->curs_pos - 1;
	else if (input == DEL)
		j = e->curs_pos;
	else
		j = e->curs_pos + 1;
	e->curs_pos = e->curs_max;
	go_to_position(e, str, j);
	e->curs_pos = j;
}

void		modif_command(t_env *e, int input, t_elem *elem)
{
	t_history	*h;

	h = elem->content;
	if (!h->command_edit)
		h->command_edit = ft_strdup(h->command);
	if ((input > 31 && input < 127))
		h->command_edit = string_insert(e, h->command_edit, input, e->curs_pos);
	else if (input == 127 || input == DEL)
		h->command_edit = delete_char(e, input, h->command_edit);
	display_command(e, input, h->command_edit);
}

void		command_memory(t_env *e, int input, t_list *lst, t_elem **elem)
{
	t_history	*h;
	char		*str;

	h = (*elem)->content;
	str = ft_strlen(h->command_edit) > 0 ? h->command_edit : h->command;
	if (e->curs_pos)
		move_cursor_line(e, HOME, str);
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	if (input == KUP && *elem != lst->head)
		*elem = (*elem)->prev;
	else if (input == KDOWN && *elem != lst->tail)
		*elem = (*elem)->next;
	h = (*elem)->content;
	str = h->command_edit ? h->command_edit : h->command;
	e->curs_max = 0;
	if (str)
	{
		ft_putstr(str);
		e->curs_max = ft_strlen(str);
		if ((e->prompt_len + e->curs_max) % e->width == 0)
			tputs(tgetstr("do", NULL), 0, ft_putchar2);
	}
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	e->curs_pos = e->curs_max;
}
