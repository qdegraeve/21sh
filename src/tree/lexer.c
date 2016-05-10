#include "tree.h"

int get_io(char *str)
{
	 if (str && str[0] == '|')
		return (3);
	else if (str && str[0] == ';')
		return (4);
	else if (str && str[0] == '>' && str[1] == '>')
		return (2);
	else if (str && str[0] == '>')
		return (1);
	else if (str && str[0] == '<' && str[1] == '<')
		return (-2);
	else if (str && str[0] == '<')
		return (-1);
	return (0);
}

static char *space_priority(char *str)
{
	if (str && str[0] == '|')
		return (&str[1]);
	else if (str && str[0] == ';')
		return (&str[1]);
	else if (str && str[0] == '>' && str[1] == '>')
		return (&str[2]);
	else if (str && str[0] == '>')
		return (&str[1]);
	else if (str && str[0] == '<' && str[1] == '<')
		return (&str[2]);
	else if (str && str[0] == '<')
		return (&str[1]);
	return (NULL);
}

static void add_all_node(t_btree **root, char *str)
{
	int		i;
	char	*tmp;
	int		priority;
	char	*save;


	i = 0;
	save = ft_strcpy(ft_strnew(ft_strlen(str)), str);
	while (save[i])
	{
		while (save[i] && ((priority = get_io(&save[i])) == 0))
			i++;
		tmp = (char *)malloc(sizeof(char) * i);
		tmp = ft_strncpy(tmp, save, i);
		btree_insert_data(root, create_infos(tmp, priority));
		if ((save = space_priority(&save[i])) == NULL)
			break;
		i = 0;
	}
}

t_btree *lexer(char *str)
{
	t_btree *root;
	int		i;
	int		j;
	char	*tmp;
	int		priority;

	priority = 0;
	i = 0;
	j = 0;
	while (str[i] && str)
	{
		if ((priority = get_io(&str[i])) != 0)
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
		root = btree_create_node(create_infos(tmp, priority));
		str = space_priority(&str[i]);
		add_all_node(&root, str);
	}
:W	return (root);
}
