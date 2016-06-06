#include "shell.h"

char	*ft_getenv(char *var, char **env)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	if (env == NULL)
		return (NULL);
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
