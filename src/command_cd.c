#include "shell.h"

char	*cd_oldpwd(t_builtin *b)
{
	char	*path;

	path = NULL;
	if ((path = ft_getenv("OLDPWD", b->env)) != NULL)
		path = ft_strjoin(path, b->argv[0] + 1);
	else
	{
		ft_putendl_fd("cd: no OLDPWD defined", 2);
		b->error = 1;
	}
	return (path);
}

void	cd_home(t_builtin *b, char *path)
{
	char		*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 255);
	if (path)
	{
		if (chdir(path) == 0)
		{
			set_env_one(b, ft_cjoin(ft_strdup("OLDPWD="), pwd), 7);
			set_env_one(b, ft_cjoin(ft_strdup("PWD="), getcwd(NULL, 255)), 4);
			ft_strdel(&path);
		}
		else
		{
			ft_putstr_fd("cd: not a directory: ", 2);
			ft_putendl_fd(b->argv[0], 2);
			ft_strdel(&pwd);
			ft_strdel(&path);
			b->error = 1;
			return ;
		}
	}
}

void	cd_path(t_builtin *b)
{
	char			*path;
	char			*pwd;

	pwd = NULL;
	path = NULL;
	if (b->argv[0][0] == '/')
		path = ft_strdup(b->argv[0]);
	else if (b->argv[0][0] == '-' && !b->argv[0][1])
		path = cd_oldpwd(b);
	else
	{
		path = ft_cjoin(getcwd(pwd, 255), ft_strdup("/"));
		path = ft_cjoin(path, ft_strdup(b->argv[0]));
	}
	cd_home(b, path);
}

void	cd_no_home(t_builtin *b)
{
	b->error = 1;
	ft_putendl_fd("cd: no home directory", 2);
}

void	exec_cd(t_builtin *b)
{
	char		*pwd;

	pwd = NULL;
	if (!b->argv[0] || !ft_strcmp(b->argv[0], "--"))
	{
		if (b->home != -1)
		{
			set_env_one(b, ft_cjoin(ft_strdup("OLDPWD="), getcwd(pwd, 255)), 7);
			chdir(ft_getenv("HOME", b->env));
			set_env_one(b, ft_cjoin(ft_strdup("PWD="), getcwd(pwd, 255)), 4);
		}
		else
			cd_no_home(b);
		return ;
	}
	if (b->argv[1])
	{
		ft_putstr_fd("cd: string not in pwd:", 2);
		ft_putendl_fd(b->argv[0], 2);
		b->error = 1;
		return ;
	}
	else
		cd_path(b);
}
