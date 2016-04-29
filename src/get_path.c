/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:39:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/04/29 16:13:09 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

const t_commands	g_code_error[6] = {{"cd", &exec_cd},
	{"env", &exec_env},
	{"setenv", &exec_setenv},
	{"unsetenv", &exec_unsetenv},
	{"exit", &exec_exit},
	{"quit", &exec_exit}};

void	get_env_index(t_builtin **b)
{
	int		i;

	i = 0;
	(*b)->path_e = -1;
	(*b)->home = -1;
	while ((*b)->env && (*b)->env[i])
	{
		if (!ft_strncmp((*b)->env[i], "PATH=", 5))
			(*b)->path_e = i;
		else if (!ft_strncmp((*b)->env[i], "HOME=", 5))
			(*b)->home = i;
		i++;
	}
	if ((*b)->path_e == -1)
	{
		set_env_one(*b, path_gen(), 5);
		get_env_index(b);
	}
}

void	exec_exit(t_builtin *b)
{
	t_elem	*elem;

	elem = b->lst.head;
	b->error = 0;
	if (b->env_cpy)
		clear_tab(b->env_cpy);
	if (b->env)
		clear_tab(b->env);
	if (b->path)
		ft_strdel(&b->path);
	if (b->argv)
		clear_tab(b->argv);
	if ((b->fd_history = open("/nfs/2015/q/qdegraev/.21sh_history", O_RDWR | O_APPEND)) < 0)
		ft_printf("fd == %d", b->fd_history);
	while (elem)
	{
		if (((t_history*)elem->content)->to_save)
			ft_putendl_fd(((t_history*)elem->content)->command, b->fd_history);
		elem = elem->next;
	}
	ft_lstdel(&b->lst, del_lst_char);
	close(b->fd_history);
	term_reset();
	exit(EXIT_SUCCESS);
}

void	get_command(char *command, t_builtin *b)
{
	int			i;

	i = 0;
	get_env_index(&b);
	while (i < 6)
	{
		if (!ft_strcmp(command, g_code_error[i].id))
		{
			b->argv = ft_tab_remove(b->argv, 0);
			g_code_error[i].f(b);
			return ;
		}
		i++;
	}
	get_path(b->argv[0], b);
}

void	no_path(t_builtin *b, char *command, char **test)
{
	if (command[0] == '.' || command[0] == '/')
		if (access(command, X_OK) == 0)
		{
			b->path = ft_strdup(command);
			clear_tab(test);
			return ;
		}
	clear_tab(test);
	b->error = 1;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(command, 2);
	b->path = NULL;
}

void	get_path(char *command, t_builtin *b)
{
	char	*path;
	char	**test;
	int		i;

	path = NULL;
	test = NULL;
	if (b->env[0])
		test = ft_strsplit(b->env[b->path_e] + 5, ':');
	i = 0;
	while (test && test[i])
	{
		test[i] = ft_cjoin(test[i], ft_strdup("/"));
		path = ft_strjoin(test[i], command);
		if (access(path, X_OK) == 0)
		{
			b->path = path;
			clear_tab(test);
			return ;
		}
		else
			ft_strdel(&path);
		i++;
	}
	no_path(b, command, test);
}
