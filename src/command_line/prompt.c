#include "shell.h"

char	*get_pwd_prompt(char *path)
{
	int		i;

	if (!path)
		path = ft_strdup("Middle of nowhere");
	i = ft_strlen(path);
	while (i >= 0 && path[i] != '/')
		i--;
	get_env()->prompt_len = ft_strlen(path + i + 1) + 5;
	return (path + i + 1);
}

void	prompt(int error)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 255);
	ft_putstr("\033[1;36m");
	if (error)
		ft_printf("%s \033[1;31m: > ", get_pwd_prompt(path));
	else
		ft_printf("%s \033[1;32m: > ", get_pwd_prompt(path));
	ft_putstr("\033[0m");
	if (path)
		ft_strdel(&path);
}

char	*get_commands(t_builtin *b)
{
	char	*line;

	line = NULL;
	init_env(get_env(), NULL);
	b->error ? prompt(1) : prompt(0);
	term_set();
	tputs(tgetstr("cd", NULL), 0, ft_putchar2);
	line = ft_strdup(get_input(b, 0));
	term_reset();
	get_env()->edit = 0;
	return (line);
}

char	**get_argv(t_builtin *b, char *command)
{
	char	**argv;

	argv = NULL;
	b->error = 0;
	argv = str_to_argv(command);
	return (argv);
}
