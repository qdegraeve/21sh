#include "shell.h"

static void	go_to_next_io(char *str, int *i, int *total, int *priority)
{
	while (ft_isdigit(str[*i]) == 1)
		count(i, total, 1);
	count(i, total, space_priority(&str[*i]));
	while ((str[*i] && ((*priority = get_io(&str[*i])) == 3)) ||
			command_complete(get_quote(), &str[*i]) == 0 || str[*i - 1] == '\\')
		count(i, total, 1);
	while (*priority < 0 && *i > 0 && ft_isdigit(str[*i - 1]) == 1)
		count(i, total, -1);
}

static void	add_pipetolist(t_cmds **root, int i)
{
	t_cmds *tmp;

	tmp = *root;
	if (i == 2 || i == 4 || i == 5)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (i == 2)
			tmp->pipe = 1;
		else if (i == 4)
			tmp->test2 = 1;
		else if (i == 5)
			tmp->test1 = 1;
	}
}

int			add_all_io(t_cmds **root, char *str)
{
	int		i;
	int		total;
	char	*tmp;
	int		priority;
	int		priority2;

	i = 0;
	total = 0;
	while (str && str[i])
	{
		priority2 = get_priority(str);
		go_to_next_io(str, &i, &total, &priority);
		tmp = ft_strncpy(ft_strnew(i), str, i);
		priority2 <= -3 ? add_io(tmp, root, 2) : add_io(tmp, root, 1);
		if (str[i] == '\0' || str[i + 1] == '\0')
			return (total);
		add_pipetolist(root, priority);
		if (priority < 0)
			str = &str[i];
		else
			return (total + (priority >= 4 ? 2 : 1));
		i = 0;
	}
	return (0);
}

static void	go_to_next_cmd(char *str, int *i, int *priority)
{
	if (*i == 0)
	{
		while (str[*i] && ft_isdigit(str[*i]) == 1)
			*i += 1;
		while (str[*i] && get_io(&str[*i]) != 3)
			*i += 1;
	}
	while ((str[*i] && (*priority = get_io(&str[*i])) == 3) ||
			command_complete(get_quote(), &str[*i]) == 0 || str[*i - 1] == '\\')
		*i += 1;
	while (*priority < 0 && *i > 0 && ft_isdigit(str[*i - 1]) == 1)
		*i -= 1;
}

t_cmds		*lexer(char *str)
{
	t_cmds		*root;
	int			i;
	char		*tmp;
	int			priority;

	priority = 0;
	i = 0;
	root = NULL;
	while (str && str[i])
	{
		go_to_next_cmd(str, &i, &priority);
		tmp = ft_strncpy(ft_strnew(i), str, i);
		add_cmds(tmp, priority, &root);
		if (priority > 0)
		{
			if (str[i] == '\0' || str[i + 1] == '\0')
				return (root);
			str = &str[i + (priority >= 4 ? 2 : 1)];
		}
		else
			str = &str[i + add_all_io(&root, &str[i])];
		i = 0;
	}
	return (root);
}
