#include "shell.h"

static char *clean_h(char *heredoc, char *compare)
{
	int		i;

	i = ft_strlen(heredoc);
	if (ft_strcmp(heredoc, compare) == 0)
			return (NULL);
	while (i > 0 && heredoc[i] != '\n')
		i--;
	heredoc[i] = '\n';
	heredoc[i + 1] = '\0';
	return (heredoc);
}

int		doc(char **input, t_builtin *b)
{
	char	*str;
	int		fd_input;

	if (ft_strlen(input[0]) == 2 && input[1] == NULL)
	{
		ft_printf("Parse Error\n");
		return (1);
	}
	else if (ft_strlen(input[0]) == 2 && input[1] != NULL)
		str = input[1];
	else
		str  = (input[0] += 2);
	fd_input = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_input < 0)
	{
		ft_putstr("Error with open\n");
		return (1);
	}
	ft_putstr_fd(clean_h(heredoc(str, b), str), fd_input);
	close(fd_input);
	fd_input = open("/tmp/.heredoc", O_RDONLY);
	dup2(fd_input, STDIN_FILENO);
	return (0);
}

int rfile(char **input)
{
	int		fd_input;
	char	*file;

	if (ft_strlen(input[0]) == 1 && input[1] == NULL)
	{
		ft_printf("Parse Error\n");
		return (1);
	}
	else if (ft_strlen(input[0]) == 1 && input[1] != NULL)
		file = input[1];
	else
		file = ++input[0];
	fd_input = open(file, O_RDONLY);
	if (fd_input < 0)
	{
		ft_printf("%s : No such file or directory\n", file);
		return (1);
	}
	dup2(fd_input, STDIN_FILENO);
	return (0);
}

int wfile(char **output)
{
	int		fd_output;
	char	*file;

	if (ft_strlen(output[0]) == 1 && output[1] == NULL)
	{
		ft_printf("Parse Error\n");
		return (1);
	}
	else if (ft_strlen(output[0]) == 1 && output[1] != NULL)
		file = output[1];
	else
		file = ++output[0];
	fd_output = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output < 0)
	{
		ft_printf("%s : Error in attribution of file descriptor\n", file);
		return (1);
	}
	dup2(fd_output, STDOUT_FILENO);
	return (0);
}

int ape(char **output)
{
	int		fd_output;
	char	*file;

	if (ft_strlen(output[0]) == 2 && output[1] == NULL)
	{
		ft_printf("Parse Error\n");
		return (1);
	}
	else if (ft_strlen(output[0]) == 2 && output[1] != NULL)
		file = output[1];
	else
		file = (output[0] += 2);
	fd_output = open(file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd_output < 0)
	{
		ft_printf("%s : Error in attribution of file descriptor\n", file);
		return (1);
	}
	dup2(fd_output, STDOUT_FILENO);
	return (0);
}

void	exec_simple(t_cli cli, t_builtin *b)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		if (cli.input != NULL)
		{
			if (get_priority(cli.input[0]) == -2 && doc(cli.input, b) == 1)
				exit(EXIT_FAILURE);
			else if (get_priority(cli.input[0]) == -1 && rfile(cli.input) == 1)
				exit(EXIT_FAILURE);
		}
		else if (cli.output != NULL)
		{
			if (get_priority(cli.output[0]) == -4 && wfile(cli.output) == 1)
				exit(EXIT_FAILURE);
			else if (get_priority(cli.output[0]) == -3 && ape(cli.output) == 1)
				exit(EXIT_FAILURE);
		}
		execve(b->path, b->argv, b->env);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
}
