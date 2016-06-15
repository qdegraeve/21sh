#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

# define KUP		4283163
# define KDOWN		4348699
# define KLEFT		4479771
# define KRIGHT		4414235
# define ESC		27
# define TAB		9
# define HOME		4741915
# define END		4610843
# define DEL		2117294875
# define LEFT_OPT	1146821403
# define RIGHT_OPT	1130044187
# define SEL_OPT	-24893
# define COPY_OPT	-22845
# define PASTE_OPT	-6715422
# define CUT_OPT	-7894814
# define LINE_UP	1096489755
# define LINE_DO	1113266971

# include "shell.h"
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <dirent.h>

typedef struct s_builtin	t_builtin;
typedef struct s_list		t_list;

typedef struct		s_quote
{
	char			quote;
	char			dquote;
	char			bquote;
}					t_quote;

typedef struct		s_env
{
	int				curs_pos;
	int				curs_max;
	int				curs_line;
	int				prompt_len;
	int				width;
	int				sel;
	char			dyn;
	char			pipe;
	char			cmdor;
	char			cmdand;
	char			edit;
	char			cmd;
	int				fd;
	char			*src;
	char			*up;
	char			*down;
	char			*le;
	char			*ri;
	char			*cd;
	char			*sc;
	char			*rc;
	char			*down_one;
	char			*up_one;
	char			*cr;
	char			**choices;
	char			*complete;
	char			*path;
	t_elem			*elem;
	t_quote			q;
	struct termios	term;
}					t_env;

typedef struct		s_history
{
	char			*command;
	char			*command_edit;
	char			to_save;
}					t_history;

/*
**		term_control.c
*/
void				init_env(t_env *e, char *src);
t_env				*get_env();
void				term_set(void);
void				term_reset(void);

/*
**		tools_cmd_line.c
*/
int					ft_putchar2(int c);

/*
**		select_mod.c
*/
void				select_mod(t_env *e, int input, t_elem **elem);

/*
**		get_input.c
*/
char				*get_input(t_builtin *b, int input);

/*
**		command_line_read.c
*/
int					keys_action(t_env *e, int input, t_list *lst);
void				list_to_string(t_list *lst, t_elem **elem);
int					get_prev_lfeed(t_env *e, char *str, int i);
int					edit_line(t_env *e, int input, t_list *lst);

/*
**					command_line_edit.c
*/
void				modif_command(t_env *e, int input, t_elem *elem);
void				command_memory(t_env *e, int input, t_list *lst,
		t_elem **elem);
char				*string_insert(t_env *e, char **src, char ins, int pos);
char				*delete_char(t_env *e, int input, char **src);

/*
**		Move cursor
*/
void				move_cursor_line(t_env *e, int input, char *str);
void				move_cursor_word(t_env *e, int input, char *str);

/*
**		Copy_paste.c
*/
void				copy_paste_mod(t_env *e, int input, t_elem **elem);
void				cut(t_env *e, char **str, t_builtin *b);

/*
**		tools.c
*/
void				del_lst_char(void *content, size_t size);
void				list_init(t_list *lst);
t_builtin			*get_buil(void);

/*
**		quote_management.c
*/
int					ft_is_quote(char c);
int					command_complete(t_quote *q, char *str);
int					command_ncomplete(t_quote *q, char *str, int len);
void				ft_quote(t_quote *q, char c);
void				quote_prompt(t_env *e);

/*
**		keys_actions.c
*/
int					calc_line(t_env *e, char *str, int pos);
int					calc_row(t_env *e, char *str, int pos);
void				go_to_position(t_env *e, char *str, int position);
void				keys_actions(t_env *e, int input, t_list *lst,
		t_elem **elem);

/*
**		dynamic_completion.c
*/
void				ft_dynamic_completion(t_env *e, t_elem *elem);
void				ft_replace_filename(t_env *e, char *path, char **str);
void				ft_restore_cursor_position(t_env *e, char *command, int line);

#endif
