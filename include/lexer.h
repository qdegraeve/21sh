#ifndef LEXER_H
#define LEXER_H

#include "shell.h"


typedef struct		s_cmds
{
	char			*cmd;
	int				pipe;
	char			*input;
	char			*output;
	struct s_cmds	*next;
}					t_cmds;

/*
** Tools
*/
void				add_cmds(char *str, int pipe, t_cmds **root);
void				add_io(char *str, t_cmds **root, int fd);
void				debug_lexer(t_cmds **tmp); // SUPRIMER CETTE LIGNE AU RENDU
int					space_priority(char *str);
int					get_io(char *str);
void				count(int *i, int *total, int counter);

/*
** LEXER
*/
t_cmds				*lexer(char *str);
int					add_all_io(t_cmds **root, char *str);
int					get_priority(char *str);
t_quote				*get_quote(void);

#endif
