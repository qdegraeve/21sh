#include "shell.h"

void	exec_simple(t_cli cli, t_builtin *b)
{
	pid_t	child;
	int		fd_input;
	int		fd_output;

	child = fork();
	if (child == -1)
		ft_putstr("blocado");
	else if (child == 0)
	{
		if (cli.input != NULL)
		{
			if (get_priority(cli.input[0]) == -2)
				ft_putstr_fd(heredoc(cli.input[1], b), STDIN_FILENO);
			else if (get_priority(cli.input[0]) == -1)
			{
				fd_input = open(cli.input[1], O_RDONLY);
				if (fd_input < 0)
				{
					ft_printf("%s : No such file or directory\n", cli.input[1]);
					return ;
				}
				dup2(fd_input, STDIN_FILENO);
			}
		}
		else if (cli.output != NULL)
		{
			if (get_priority(cli.output[0]) == -3)
			{
				fd_output = open(cli.output[1], O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
				if (fd_output < 0)
					return ;
				dup2(fd_output, STDOUT_FILENO);
			}
			else if (get_priority(cli.output[0]) == -4)
			{
				fd_output = open(cli.output[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_output < 0)
					return ;
				dup2(fd_output, STDOUT_FILENO);
			}
		}
		execve(b->path, b->argv, NULL);
	}
	wait(NULL);
}

