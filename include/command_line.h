#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

# define KUP		4283163
# define KDOWN		4348699
# define KLEFT		4479771
# define KRIGHT		4414235
# define ESC		27
# define HOME		4741915
# define END		4610843
# define LEFT_OPT	1146821403
# define RIGHT_OPT	1130044187
# define COPY_OPT	-22845
# define PASTE_OPT	-6715422
# define CUT_OPT	-7894814

# include "shell.h"
# include <termios.h>
# include <term.h>

typedef struct		s_builtin	t_builtin;
typedef struct		s_list		t_list;

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
	t_elem			*elem;
	struct termios	term;
}					t_env;

typedef struct	history
{
	char		*command;
	char		*command_edit;
	char		to_save;
}				t_history;

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
void	command_memory(t_env *e, int input, t_list *lst, t_elem **elem);

/*
**  Move cursor
*/
void move_cursor_line(t_env *e, int input, char *str);
void move_cursor_word(t_env *e, int input, char *str);

/*
**
*/
void copy_paste_mod(t_env *e, int input, t_elem **elem);

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
