#ifndef TREE_H
#define TREE_H

#include "shell.h"

typedef struct s_io
{
	char	*str;
	struct s_io *next;
}				t_io;

typedef struct s_cmds
{
	char		*cmd;
	int			pipe;
	struct s_io *input;
	struct s_io *output;
	struct s_cmds *next;
}				t_cmds;

/*
** Tools
*/
void	add_cmds(char *str, int pipe, t_cmds **root);
void	add_io(char *str, t_cmds **root, int fd);
void	debug_lexer(t_cmds **tmp);
int		space_priority(char *str);
int		get_io(char *str);
void	count(int *i, int *total, int counter);

/*
** LEXER
*/
t_cmds	*lexer(char *str);
int add_all_io(t_cmds **root, char *str);
#endif
