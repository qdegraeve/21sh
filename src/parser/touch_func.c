/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:12:25 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:12:25 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	output_to_argv(t_cmds *tmp, t_io *last)
{
	while (last->next != NULL)
	{
		touch_file(last->io);
		last = last->next;
	}
	tmp->tab_o = str_to_argv(last->io);
	if (ft_is_agregator(tmp->tab_o[0]) == 0)
		touch_file(last->io);
	clean_quote(tmp->tab_o);
}

void		io_to_argv(t_cmds *tmp, int nb)
{
	t_io *last;

	while (nb-- > 0)
	{
		last = tmp->input;
		if (last)
		{
			while (last->next)
				last = last->next;
			tmp->tab_i = str_to_argv(last->io);
			clean_quote(tmp->tab_i);
		}
		last = tmp->output;
		if (last)
			output_to_argv(tmp, last);
		tmp = tmp->next;
	}
}

static int	touch_erase(char **file)
{
	char	*path;
	int		fd;

	fd = -1;
	if (ft_strlen(file[0]) == 1 && file[1] == NULL)
		return (1);
	else if (file[1] != NULL)
		path = file[1];
	else
		path = go_to_file(file[0], 1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd);
	return (0);
}

static int	juste_touch(char **file)
{
	char	*path;
	int		fd;

	fd = -1;
	if (ft_strlen(file[0]) == 2 && file[1] == NULL)
		return (1);
	else if (file != NULL)
		path = file[1];
	else
		path = go_to_file(file[0], 2);
	fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0644);
	close(fd);
	return (0);
}

void		touch_file(char *str)
{
	char	**file;

	file = str_to_argv(str);
	if (get_priority(file[0]) == -4 && touch_erase(file) == 1)
		return ;
	else if (get_priority(file[0]) == -3 && juste_touch(file) == 1)
		return ;
	free(file);
}
