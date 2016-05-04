#include "shell.h"

int		get_prev_lfeed(t_env *e, char *str, int i)
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

int		edit_line(t_env *e, int input, t_list *lst)
{
	static t_elem	*elem = NULL;
	t_history		h;
	t_history		*h1;
	char			*str;
	int				i = 0;

	if (!elem)
	{
		ft_bzero(&h, sizeof(t_history));
		ft_lstadd_last(lst, &h, sizeof(t_history));
		elem = lst->tail;
	}
	h1 = elem->content;
	str = h1->command_edit ? h1->command_edit : h1->command;
	if (input > 31 && input < 127)
		write_char(e, (char)input, elem);
	else if (input == 127 && e->curs_pos != 0)
		h1->command_edit = delete_char(e, h1->command_edit ? h1->command_edit : h1->command);
	else if (input == KLEFT && e->curs_pos)
	{
		if (str[e->curs_pos - 1] == '\n')
		{
			if ((i = get_prev_lfeed(e, str, e->curs_pos - 1)))
				tputs(tgoto(tgetstr("RI", NULL), 0, i), 0, ft_putchar2);
			tputs(tgetstr("up", NULL), 0, ft_putchar2);
		}
		else if (!((e->curs_pos + e->prompt_len) % e->width))
		{
			tputs(tgoto(tgetstr("RI", NULL), 0, e->width), 0, ft_putchar2);
			tputs(tgetstr("up", NULL), 0, ft_putchar2);
		}
		else
			tputs(tgetstr("le", NULL), 0, ft_putchar2);
		e->curs_pos--;
	}
	else if (input == KRIGHT && e->curs_pos < e->curs_max)
	{
		if (!((e->curs_pos + e->prompt_len + 1) % e->width) || str[e->curs_pos + 1] == '\n')
		{
			tputs(tgoto(tgetstr("LE", NULL), 0, e->width), 0, ft_putchar2);
			tputs(tgetstr("do", NULL), 0, ft_putchar2);
		}
		else
			tputs(tgetstr("nd", NULL), 0, ft_putchar2);
		e->curs_pos++;
	}
	else if ((input == KUP && elem->prev) || (input == KDOWN && elem->next))
		elem = command_memory(e, input, lst, elem);
	else if (input == END || input == HOME)
		move_cursor_line(e, input);
	else if (input == LEFT_OPT || input == RIGHT_OPT)
		move_cursor_word(e, input);
	else if (input == 10)
	{
		list_to_string(lst, elem);
		if (!command_complete(get_env()))
		{
			h1->command = ft_cjoin(h1->command, ft_strdup("\n"));
			h1->command_edit = ft_strnew(0);
			e->curs_pos = 0;
			e->curs_max = 0;
		}
		else if (h1->command)
			elem = lst->tail->next;
	}
	return (0);
}

void	list_to_string(t_list *lst, t_elem *elem)
{
	t_history	*h;
	char		*str;

	str = ((t_history*)lst->tail->content)->command;
	h = elem->content;
	if (h->command_edit)
		((t_history*)lst->tail->content)->command = ft_cjoin(str, h->command_edit);
	h->to_save = 1;
}

char	*get_input(t_builtin *b)
{
	int		input;
	char	buf[8];

	ft_bzero(buf, 4);
	term_set();
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	get_env()->width = tgetnum("co");
	input = 0;
	while (42)
	{
		if (input == 10)
		{
			ft_putchar_fd('\n', get_env()->fd);
			if (command_complete(get_env()))
			{
				term_reset();
				return (((t_history*)b->lst.tail->content)->command);
			}
			else
				quote_prompt(get_env());
		}
		input = 0;
		read(0, buf, 7);
		buf[7] = '\0';
		input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
		//		ft_printf("input == %d\n", input);
		//		ft_printf("input == %s\n", buf + 4);
		edit_line(get_env(), input, &b->lst);
		ft_bzero(buf, 4);
	}
}
