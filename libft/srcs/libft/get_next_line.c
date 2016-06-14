#include "get_next_line.h"

char	*biggerbuf(int const fd, char *buf, int *ret)
{
	char	*tmp;

	tmp = ft_strnew(BUF_SIZE);
	*ret = read(fd, tmp, BUF_SIZE);
	tmp[*ret] = '\0';
	buf = ft_cjoin(buf, tmp);
	return (buf);
}

int		get_next_line(int const fd, char **line)
{
	static char	*buf = NULL;
	int			ret;
	char		*str;

	if (!line || fd < 0)
		return (-1);
	ret = 1;
	if (buf == NULL)
		buf = ft_strnew(0);
	while (ret > 0)
	{
		if ((str = ft_strchr(buf, '\n')) != NULL)
		{
			*str = '\0';
			*line = ft_strdup(buf);
			ft_memmove(buf, str + 1, ft_strlen(str + 1) + 1);
			return (1);
		}
		buf = biggerbuf(fd, buf, &ret);
	}
	return (ret);
}
