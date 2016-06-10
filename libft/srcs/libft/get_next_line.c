#include "get_next_line.h"

#include "get_next_line.h"

char	*biggerbuf(int const fd, char *buf, int *ret)
{
	char	tmp[BUF_SIZE + 1];
	char	*tmp2;

	*ret = read(fd, tmp, BUF_SIZE);
	tmp[*ret] = '\0';
	tmp2 = buf;
	buf = ft_strjoin(buf, tmp);
	ft_strdel(&tmp2);
	return (buf);
}

int		get_next_line(int const fd, char **line)
{
	static char	*buf = "";
	int			ret;
	char		*str;

	if (!line || fd < 0)
		return (-1);
	ret = 1;
	if (buf[0] == '\0')
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
//char	*clear_tmp(char *tmp, int k)
//{
//	char *stock;
//
//	stock = NULL;
//	stock = ft_strnew(ft_strlen(tmp + k));
//	ft_strncpy(stock, tmp + k, ft_strlen(tmp + k));
//	ft_strdel(&tmp);
//	return (stock);
//}
//
//char	*new_join(char *tmp, char *buf)
//{
//	char	*stock;
//
//	stock = NULL;
//	stock = ft_strjoin(tmp, buf);
//	if (tmp)
//		ft_strdel(&tmp);
//	ft_strdel(&buf);
//	return (stock);
//}
//
//int		check_linefeed(char *s)
//{
//	int			i;
//
//	i = 0;
//	if (s == NULL)
//		return (-1);
//	while (s[i])
//	{
//		if (s[i] == '\n')
//			return (i);
//		i++;
//	}
//	return (-1);
//}
//
//int		get_next_line(int const fd, char **line)
//{
//	int			ret;
//	int			k;
//	static char	*tmp[256] = {NULL};
//	char		*buf;
//
//	buf = NULL;
//	buf = ft_strnew(BUF_SIZE);
//	if ((ret = read(fd, buf, BUF_SIZE)) == -1 || line == NULL || buf == NULL)
//		return (-1);
//	buf[ret] = '\0';
//	tmp[fd] = new_join(tmp[fd], buf);
//	k = check_linefeed(tmp[fd]);
//	(ret == 0 && !tmp[fd][0]) ? ft_strdel(&tmp[fd]) : 0;
//	if (ret == 0 && !tmp[fd])
//		return (0);
//	if (k >= 0 || (k == -1 && ret < BUF_SIZE))
//	{
//		*line = (k >= 0) ? ft_strsub(tmp[fd], 0, k) : ft_strdup(tmp[fd]);
//		if (k == -1)
//			ft_strdel(&tmp[fd]);
//		else
//			tmp[fd] = clear_tmp(tmp[fd], k + 1);
//		return (1);
//	}
//	return (get_next_line(fd, line));
//}
