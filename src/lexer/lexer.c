#include "shell.h"

static int get_priority(char *str)
{
	int		priority;
	int		i;

	priority = 0;
	i = 0;
	while (str[i] && (priority = get_io(&str[i])) == 3)
			i++;
	return (priority);
}


int add_all_io(t_cmds **root, char *str)
{
	int		i;
	int		total;
	char	*tmp;
	int		priority;
	int		priority2;

	i = 0;
	total = 0;
	while (str[i] && str)
	{
		priority2 = get_priority(str);
		while (ft_isdigit(str[i]) == 1)
			count(&i, &total, 1);
		count(&i, &total, space_priority(&str[i]));
		while (str[i] && ((priority = get_io(&str[i])) == 3))
			count(&i, &total, 1);
		while (priority < 0 && i > 0 && ft_isdigit(str[i - 1]) == 1)
			count(&i, &total, -1);
		tmp = ft_strncpy(ft_strnew(i), str, i);
		priority2 <= -3 ? add_io(tmp, root, 2) : add_io(tmp, root, 1);
		if (str[i] == '\0' || str[i + 1] == '\0')
			return (total);
		if (priority < 0)
		{
			str = &str[i];
			i = 0;
		}
		else
			return (total + 1);
	}
	return (0);
}

t_cmds *lexer(char *str)
{
	t_cmds *root = NULL;
	int		i;
	char	*tmp;
	int		priority;

	priority = 0;
	i = 0;
	while (str[i] && str)
	{
		while (str[i] && (priority = get_io(&str[i])) == 3)
			i++;
		while (priority < 0 && i > 0 && ft_isdigit(str[i - 1]) == 1)
			i--;
		tmp = (char *)malloc(sizeof(char) * i);
		ft_strncpy(tmp, str, i);
		add_cmds(tmp, (priority == 2 ? 1 : 0), &root);
		if (priority == 1 || priority == 2 || priority == 3)
		{
			if (str[i] == '\0' || str[i + 1] == '\0')
				return (root);
			str = &str[i + 1];
		}
		else
			str = &str[i + add_all_io(&root, &str[i])];
		i = 0;
	}
	return (root);
}
