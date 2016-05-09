/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 14:22:43 by qdegraev          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/05/06 15:47:50 by nahmed-m         ###   ########.fr       */
=======
/*   Updated: 2016/05/06 12:54:48 by qdegraev         ###   ########.fr       */
>>>>>>> 0a927e17e0bb46cc4c4e31f0a79251e958150614
/*                                                                            */
/* ************************************************************************** */

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
	b->argv = get_argv(b, command);
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
	int		i;
	char	*file;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	i = 0;
	b->env_cpy = NULL;
	b->error = 0;
	file = ft_strjoin(getpwuid(getuid())->pw_dir, "/.21sh_history");
	if ((b->fd_history = open(file, O_CREAT | O_RDWR, mode)) < 0)
		ft_printf("fd == %d", b->fd_history);
	ft_strdel(&file);
	get_history(b);
	while (42)
	{
		i = 0;
		b->commands = get_commands(b);
		while (b->commands && b->commands[i])
		{
			init_builtin(b, b->commands[i]);
			if (b->argv[0])
				get_command(b->argv[0], b);
			if (b->path)
				do_fork(b);
			i++;
		}
		if (b->commands)
			clear_tab(b->commands);
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
	b->env = NULL;
	b->paste = NULL;
	if (ac != 1 || av[1])
		return (0);
	ft_bzero(b, sizeof(t_builtin));
	if (env[0])
		b->env = ft_tab_strcpy(env);
	sh_level(b);
	signal_catcher();
	loop_fork(b);
	return (0);
}
