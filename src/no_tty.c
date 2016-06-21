#include "shell.h"

static void	no_tty2(t_builtin *b, char c)
{
	if (c < 0 || c > 127)
	{
		ft_putendl("unexpected token in command line\n");
		exec_exit(b);
	}
}

void		no_tty(t_builtin *b)
{
	char	*line;
	t_cmds	*root;
	int		j;
	int		i;

	line = NULL;
	i = 0;
	signal(SIGINT, SIG_DFL);
	while (get_next_line(STDIN_FILENO, &line) == 1 && i < 1000)
	{
		j = -1;
		while (line && line[++j])
			no_tty2(b, line[j]);
		if ((root = lexer(line)))
		{
			parser(&root, b);
			del_lex_io(&root);
		}
		if (line)
			ft_strdel(&line);
		i++;
	}
	exec_exit(b);
}
