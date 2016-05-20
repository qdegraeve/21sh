#include "shell.h"
#include <pwd.h>

void	init_builtin(t_builtin *b, char *command)
{
	if (b->env_cpy)
	{
		clear_tab(b->env);
		b->env = b->env_cpy;
		b->env_cpy = NULL;
	}
	if (b->path)
		ft_strdel(&b->path);
	if (b->argv)
		clear_tab(b->argv);
	b->env_i = 0;
	b->env_p = 0;
	b->env_u = 0;
	b->env_v = 0;
	b->path_e = -1;
	b->home = -1;
	b->error = 0;
	b->argv = str_to_argv(command);
}

void	get_history(t_builtin *b)
{
	t_history		h;

	list_init(&b->lst);
	ft_bzero(&h, sizeof(t_history));
	while (get_next_line(b->fd_history, &h.command) > 0)
	{
		ft_lstadd_last(&b->lst, &h, sizeof(t_history));
		ft_bzero(&h, sizeof(t_history));
	}
	close(b->fd_history);
	b->fd_history = -1;
}

void	loop_fork(t_builtin *b)
{
	char	*file;
	t_cmds	*root;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	b->env_cpy = NULL;
	b->error = 0;
	file = ft_strjoin(getpwuid(getuid())->pw_dir, "/.21sh_history");
	if ((b->fd_history = open(file, O_CREAT | O_RDWR, mode)) < 0)
		ft_printf("fd == %d", b->fd_history);
	ft_strdel(&file);
	get_history(b);
	while (42)
	{
		b->command = get_commands(b);
		init_builtin(b, b->command);
		root = NULL;
		root = lexer(b->command);
		debug_lexer(&root);
		if (root)
			parser(&root, b);
		if (b->command)
			ft_strdel(&b->command);
	}
}

void	sh_level(t_builtin *b)
{
	char	*level;
	char	*tmp;

	level = NULL;
	tmp = NULL;
	level = ft_getenv("SHLVL", b->env);
	if (level == NULL)
		tmp = ft_strdup("1");
	else
		tmp = ft_itoa(ft_atoi(level) + 1);
	set_env_one(b, ft_strjoin("SHLVL=", tmp), 6);
	ft_strdel(&tmp);
}

int		main(int ac, char **av, char **env)
{
	t_builtin *b;

	b = get_buil();
	if (ac != 1 || av[1])
		return (0);
	if (env[0])
		b->env = ft_tab_strcpy(env);
	sh_level(b);
	signal_catcher();
	loop_fork(b);
	return (0);
}
