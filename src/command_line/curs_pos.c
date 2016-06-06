#include "shell.h"

void	parse_pos(t_env *e, char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		ft_printf("%d -- ", str[i]);
		i++;
	}
	e->li_left = e->height - ft_atoi(str + i);
	ft_printf("li_left == %d height == %d\n", e->li_left, e->height);
	ft_putendl(str + i);
}

void	get_curs_pos(t_env *e)
{
	int fd_input;
	char *buf;

	buf = NULL;
	fd_input = open("/tmp/.parse", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(fd_input, "\033[6n", 20);
	close(fd_input);
	fd_input = open("/tmp/.parse", O_RDONLY);
	get_next_line(fd_input, &buf);
	close(fd_input);
	ft_putstr(buf);
	parse_pos(e, buf);
	ft_strdel(&buf);
}
