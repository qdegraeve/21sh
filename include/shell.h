#ifndef SHELL_H
# define SHELL_H

# define KUP	4283163
# define KDOWN	4348699
# define KLEFT	4479771
# define KRIGHT	4414235
# define ESC	27
# define HOME 4741915
# define END 4610843
# define LEFT_OPT 1146821403
# define RIGHT_OPT 1130044187
# define COPY_OPT -22845
# define PASTE_OPT -6715422
# define CUT_OPT -7894814
# include "../libft/include/ft_printf.h"
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <termios.h>
//# include <termcap.h>
# include <term.h>

typedef struct	s_builtin
{
	char		**env;
	char		**env_cpy;
	char		**commands;
	char		**argv;
	char		*path;
	char		*paste;
	int			path_e;
	int			home;
	char		error;
	char		env_i;
	char		env_p;
	char		env_v;
	char		env_u;
	char		env_or_cpy;
	int			fd_history;
	t_list		lst;
}				t_builtin;

typedef struct		s_env
{
	int				curs_pos;
	int				curs_max;
	int				curs_line;
	int				prompt_len;
	int				width;
	int				length;
	char			on;
	int				line;
	int				col;
	int				up;
	int				fd;
	char			quote;
	char			dquote;
	char			bquote;
	char			par;
	struct termios	term;
}					t_env;

typedef struct	history
{
	char		*command;
	char		*command_edit;
	char		to_save;
}				t_history;

typedef struct	s_commands
{
	char		*id;
	void		(*f)(t_builtin*);
}				t_commands;

typedef struct stat	t_stat;

/*
**		21sh main
*/
void			loop_fork(t_builtin *b);
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
**		signals.c
*/
void	signal_catcher(void);
void	restart(int sig);
void	suspend(int sig);
void	resize(int sig);
void	end_select(int sig);

/*
**		array_funcions.c
*/
char			**ft_tab_strcpy(char **to_copy);
void			clear_tab(char **array);
char			**ft_tab_remove(char **array, int line);
char			**ft_tab_add(char **array, char *var);
void			ft_print_tab(char **array);

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

/*
**		term_control.c
*/
void	init_env(t_env *e);
t_env	*get_env();
void	term_set(void);
void	term_reset(void);
int		ft_putchar2(int c);
void	initial_position();

/*
**		command_line_read.c
*/
int		keys_action(t_env *e, int input, t_list *lst);
char	*get_input(t_builtin *b);
void	list_to_string(t_list *lst, t_elem **elem);
int		get_prev_lfeed(t_env *e, char *str, int i);

/*
**		command_line_edit.c
*/
void	write_char(t_env *e, char input, t_elem *elem);
char	*delete_char(t_env *e, char *src);
t_elem	*command_memory(t_env *e, int input, t_list *lst, t_elem *elem);

/*
**  Move cursor
*/
void move_cursor_line(t_env *e, int input, char *str);
void move_cursor_word(t_env *e, int input, char *str);

/*
**
*/
void copy_paste_mod(t_env *e, int input, char *str, t_elem **elem);
/*
**		tools.c
*/
void	del_lst_char(void *content, size_t size);
void	list_init(t_list *lst);
t_builtin *get_buil(void);
/*
**		quote_management.c
*/
int		ft_is_quote(char c);
int		command_complete(t_env *e);
void	ft_quote(t_env *e, char c);
void	quote_prompt(t_env *e);

/*
**		keys_actions.c
*/
int		calc_line(t_env *e, char *str, int pos);
int		calc_row(t_env *e, char *str, int pos);
void	go_to_position(t_env *e, char *str, int position);
void	keys_actions(t_env *e, int input, t_list *lst, t_elem **elem);

#endif
