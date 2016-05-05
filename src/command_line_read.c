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
	t_history		*h;

	if (!elem)
	{
		ft_lstadd_last(lst, &h, sizeof(t_history));
		elem = lst->tail;
		ft_bzero((t_history*)elem->content, sizeof(t_history));
	}
	if (input != 10)
		keys_actions(e, input, lst, &elem);
	else
	{
		list_to_string(lst, &elem);
		h = elem->content;
		if (!command_complete(get_env()))
		{
			h->command = ft_cjoin(h->command, ft_strdup("\n"));
			h->command_edit = ft_strnew(0);
			e->curs_pos = 0;
			e->curs_max = 0;
		}
		else if (ft_strlen(h->command) > 0)
			elem = lst->tail->next;
	}
	return (0);
}

void	list_to_string(t_list *lst, t_elem **elem)
{
	t_history	*h;
	char		*str;

	str = ((t_history*)lst->tail->content)->command;
	h = (*elem)->content;
	if (h->command_edit)
	{
		if (*elem == lst->tail)
			((t_history*)lst->tail->content)->command = ft_cjoin(str, ft_strdup(h->command_edit));
		else
			((t_history*)lst->tail->content)->command = ft_strjoin(str, h->command_edit);
	}
	else if (*elem != lst->tail)
		((t_history*)lst->tail->content)->command = ft_strdup(h->command);
	if (h->command_edit)
		ft_strdel(&h->command_edit);
	h->command_edit = NULL;
	h->to_save = 1;
	*elem = lst->tail;
}

char	*get_input(t_builtin *b)
{
	int		input;
	int		r;
	char	buf[8];

	ft_bzero(buf, 4);
	term_set();
	tputs(tgetstr("sc", NULL), 0, ft_putchar2);
	get_env()->width = tgetnum("co");
	input = 0;
	while (42)
	{
		r = 0;
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
		r = read(0, buf, 7);
		buf[7] = '\0';
		input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
	//	ft_printf("read == %d -- input == %d\n", r, input);
		//		ft_printf("input == %s\n", buf + 4);
		edit_line(get_env(), input, &b->lst);
		ft_bzero(buf, 4);
	}
}
