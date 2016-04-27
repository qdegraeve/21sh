/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 14:56:32 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/30 16:46:48 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var, char **env)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	while (env && env[i])
	{
		if (!ft_strncmp(tmp, env[i], len))
		{
			ft_strdel(&tmp);
			return (env[i] + len);
		}
		i++;
	}
	ft_strdel(&tmp);
	return (NULL);
}

char	*path_gen(void)
{
	int		fd;
	int		i;
	char	*line;
	char	*path;

	line = NULL;
	i = 0;
	path = ft_strdup("PATH=");
	fd = open("/etc/paths", O_RDONLY);
	while (get_next_line(fd, &line) != 0)
	{
		if (i)
			path = ft_cjoin(path, ft_strdup(":"));
		path = ft_cjoin(path, line);
		i++;
	}
	return (path);
}
