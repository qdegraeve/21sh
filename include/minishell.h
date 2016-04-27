/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:34:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/31 14:47:16 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct	s_builtin
{
	char		**env;
	char		**env_cpy;
	char		**commands;
	char		**argv;
	char		*path;
	int			path_e;
	int			home;
	char		error;
	char		env_i;
	char		env_p;
	char		env_v;
	char		env_u;
	char		env_or_cpy;
}				t_builtin;

typedef struct	s_commands
{
	char		*id;
	void		(*f)(t_builtin*);
}				t_commands;

typedef struct stat	t_stat;

/*
**		minishell
*/
void			loop_fork(t_builtin b);
void			sig_handler(int sig);
void			init_builtin(t_builtin *b, char *command);

/*
**		prompt
*/
char			*get_pwd_prompt(char *path);
void			prompt(int error);
char			**get_commands(t_builtin *b);
char			**get_argv(t_builtin *b, char *command);
char			*quotes(char *line);

/*
**		do_fork
*/
void			do_fork(t_builtin *b);

/*
**		get_env
*/
char			*ft_getenv(char	*var, char **env);
char			*path_gen();

/*
**		get_path
*/
void			get_path(char *command, t_builtin *b);
void			get_command(char *command, t_builtin *b);
void			get_env_index(t_builtin **b);
void			exec_exit(t_builtin *b);

/*
**		tools
*/
char			**ft_tab_strcpy(char **to_copy);
void			clear_tab(char **tab);
char			**ft_tab_remove(char **tab, int line);
char			**ft_tab_add(char **tab, char *var);
void			ft_print_tab(char **tab);

/*
**		exec_cd
*/
void			exec_cd(t_builtin *b);
void			cd_no_home(t_builtin *b);
void			cd_path(t_builtin *b);
void			cd_home(t_builtin *b, char *path);
char			*cd_oldpwd(t_builtin *b);

/*
**		env
*/
void			exec_env	(t_builtin *b);
void			env_options(t_builtin *b, char *av);
void			set_env_options(t_builtin *b);

/*
**		set / unset -- env
*/
void			exec_setenv(t_builtin *b);
void			exec_unsetenv(t_builtin *b);
void			set_env_one(t_builtin *b, char *add, int j);
void			unset_env_one(char *remove, t_builtin *b);

#endif
