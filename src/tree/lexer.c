#include "tree.h"

char get_io(char *str)
{
	if (str[0] == '|' || str[0] == ';')
		return (1);
	else if (str[0] == '>' && str[1] == '>')
		return (2);
	else if (str[0] == '>')
		return (1);
	else if (str[0] == '<' && str[1] == '<')
		return (-2);
	else if (str[1] == '<')
		return (-1);
	return (0);
}

static void add_all_node(t_btree **root, char *str)
{
	int		i;
	char	*tmp;
	int		priority;

	i = 0;
	ft_printf("%s\n", str);
	while (str[i])
	{
		if ((priority = get_io(&str[i])) != 0)
		{
			str = &str[priority > 0 ? priority + i : ft_abs(priority) + i + 1];
			i = 0;
			while (!(get_io(&str[i]) != 0) && str[i])
				i++;
			ft_putstr(str);
			tmp = (char *)malloc(sizeof(char) * i);
			tmp = ft_strncpy(tmp, str, i);
			btree_insert_data(root, create_infos(tmp, priority));
			str = &str[i];
			i = 0;
			ft_printf("\n--%s", str);
		}
		i++;
	}
}

t_btree *lexer(char *str)
{
	t_btree *root;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (get_io(&str[i]) != 0)
		{
			j = i;
			break;
		}
		i++;
	}
	if (j == 0)
		root = btree_create_node(create_infos(str, 0));
	else
	{
		tmp = (char *)malloc(sizeof(char) * i);
		ft_strncpy(tmp, str, i);
		root = btree_create_node(create_infos(tmp, 0));
		add_all_node(&root, &str[i]);
	}
	return (root);
}
