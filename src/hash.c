#include "shell.h"

char	*triple_join(char *front, char *middle, char *back, char del)
{
	char	*dest;
	int		len;

	dest = NULL;
	len = ft_strlen(front) + ft_strlen(middle) + ft_strlen(back);
	dest = ft_strnew(len);
	if (front)
		dest = ft_strcpy(dest, front);
	if (middle)
		dest = ft_strcat(dest, middle);
	if (back)
		dest = ft_strcat(dest, back);
	if (del && front)
		ft_strdel(&front);
	return (dest);
}

void	get_list_cmd2(DIR **repository, char **tmp, char *test)
{
	struct dirent	*content;
	char			*path;

	path = NULL;
	while ((content = readdir(*repository)) != NULL)
	{
		path = triple_join(test, "/", content->d_name, 0);
		if (content->d_name[0] != '.' && access(path, X_OK) == 0)
			*tmp = triple_join(*tmp, " ", content->d_name, 1);
		ft_strdel(&path);
	}
	closedir(*repository);
}

void	get_list_cmd(t_builtin *b)
{
	DIR				*repository;
	char			**test;
	char			*tmp;
	int				i;

	test = NULL;
	tmp = NULL;
	if (b->env[0])
		test = ft_strsplit(ft_getenv("PATH", get_buil()->env), ':');
	i = 0;
	while (test && test[i])
	{
		repository = opendir(test[i]);
		if (repository != NULL)
			get_list_cmd2(&repository, &tmp, test[i]);
		i++;
	}
	b->cmd_hash = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
}
