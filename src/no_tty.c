#include "shell.h"

void		no_tty(t_builtin *b)
{
	char	*line;
	t_cmds	*root;
	int		j;

	while (get_next_line(STDIN_FILENO, &line) == 1)
	{
		j = -1;
		while (line[++j])
			if (line[j] < 0 || line[j] > 127)
			{
				ft_printf("unexpected token in command line\n");
				exec_exit(b);
			}
		root = NULL;
		root = lexer(line);
		if (root)
			parser(&root, b);
		if (line)
			ft_strdel(&line);
		if (root)
			del_lex_io(&root);
	}
	exec_exit(b);
}
