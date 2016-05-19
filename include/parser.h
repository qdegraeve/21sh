#ifndef PARSER_H
# define PARSER_H

#include "shell.h"
#include "lexer.h"

typedef struct	s_cli
{
	char		**cmd;
	char		**input;
	char		**output;
}				t_cli;
/*
** PARSER
*/
void			parser(t_cmds **root);
char			**str_to_argv(char const *s);

/*
** EXEC
*/
void			exec_simple(t_cmds *cmd);

/*
** Heredoc.c
*/
char			*heredoc(char *src, t_builtin *b);

#endif
