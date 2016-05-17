#include "shell.h"

	void	exec_simple(t_cmds *cmd)
	{
		pid_t	child;
		int		fd_input;
		int		fd_output;
		int		i = 0;

		child = fork();
		if (child == -1)
			ft_putstr("blocado");
		else if (child == 0)
		{
			if (cmd->input != NULL)
			{
				if (get_priority(cmd->input) == -1)
				{
					fd_input = open(ft_strsplit(cmd->input, ' ')[1], O_RDONLY);
					if (fd_input < 0)
					{
						ft_printf("%s : No such file or directory", ft_strsplit(cmd->input, ' ')[1]);
						return ;
					}
					dup2(fd_input, STDIN_FILENO);
				}
				else if (get_priority(cmd->input) == -2)
				{
					ft_putstr("heredoc code");
				}
			}
			else if (cmd->output != NULL)
			{
				if (get_priority(cmd->output) == -3)
				{
					fd_output = open(ft_strsplit(cmd->output, ' ')[1], O_WRONLY | O_APPEND | O_CREAT);
					if (fd_input < 0)
						return ;
					dup2(fd_output, STDOUT_FILENO);
				}
				else if (get_priority(cmd->output) == -4)
				{
					fd_output = open(ft_strsplit(cmd->output, ' ')[1], O_WRONLY | O_CREAT | O_TRUNC);
					if (fd_input < 0)
						return ;
					dup2(fd_output, STDOUT_FILENO);
				}
			}
//			execve( ,NULL);
		}
	wait(NULL);
}

