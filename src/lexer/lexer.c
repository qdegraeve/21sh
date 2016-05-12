#include "lexer.h"

int get_io(char *str)
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

static int space_priority(char *str)
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

int add_all_io(t_cmds **root, char *str)
{
	int		i;
	int		total;
	t_io	*io = NULL;
	char	*tmp;
	int		priority;

	priority = 0;
	i = 0;
	total = 0;
	while (str[i] && str)
	{
		while (ft_isdigit(str[i]) == 1)
			i++;
		i += space_priority(&str[i]);
		while (str[i] && ((priority = get_io(&str[i])) == 3))
			i++;
		tmp = (char *)malloc(sizeof(char) * i);
		tmp = ft_strncpy(tmp, str, i);
		if (priority < 0)
		{

		}
		else
			return (total + i);
//		btree_insert_data(root, create_infos(tmp, priority));
//		if ((save = space_priority(&save[i])) == NULL)
//			break;
//		i = 0;
	}
return (1);
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
		if (priority == 1 || priority == 2 || priority == 3)
		{
			add_cmds(tmp, (priority == 2 ? 1 : 0), &root);
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
