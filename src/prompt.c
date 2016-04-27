/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 16:47:58 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/31 14:38:47 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd_prompt(char *path)
{
	int		i;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	return (path + i + 1);
}

void	prompt(int error)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 255);
	ft_putstr_fd("\033[1;36m", 1);
	if (error)
		ft_printf("%s \033[1;31m: > ", get_pwd_prompt(path));
	else
		ft_printf("%s \033[1;32m: > ", get_pwd_prompt(path));
	ft_putstr_fd("\033[0m", 1);
	ft_strdel(&path);
}

char	*quotes(char *line)
{
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	while (line && line[i])
	{
		if (!quote && (line[i] == ' ' || line[i] == '\t'))
			line[i] = 130;
		if (!quote && line[i] == '"')
		{
			line[i] = 130;
			quote++;
		}
		if (quote && line[i] == '"')
		{
			line[i] = 130;
			quote--;
		}
		i++;
	}
	return (line);
}

char	**get_commands(t_builtin *b)
{
	char	*line;
	char	**commands;
	int		g;

	line = NULL;
	commands = NULL;
	g = 0;
	b->error ? prompt(1) : prompt(0);
	if (get_next_line(0, &line) == 0)
	{
		ft_printf("\n");
		exec_exit(b);
	}
	commands = ft_strsplit(line, ';');
	if (line)
		ft_strdel(&line);
	return (commands);
}

char	**get_argv(t_builtin *b, char *command)
{
	char	**argv;

	argv = NULL;
	b->error = 0;
	command = quotes(command);
	argv = ft_strsplit(command, 130);
	return (argv);
}
