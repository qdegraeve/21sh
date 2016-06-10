#include "shell.h"

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
			if (line[j] < 0 || line[j] > 127)
			{
				ft_printf("unexpected token in command line\n");
				exec_exit(b);
			}
		root = lexer(line);
		if (root)
			parser(&root, b);
		if (line)
			ft_strdel(&line);
		if (root)
			del_lex_io(&root);
		i++;
	}
	exec_exit(b);
}
