#ifndef PARSER_H
# define PARSER_H

# include "shell.h"
# include "lexer.h"

typedef struct	s_cli
{
	char		**input;
	char		**output;
}				t_cli;

/*
** PARSER
*/
void			parser(t_cmds **root, t_builtin *b);
char			**str_to_argv(char const *s);
void			clean_quote(char **line);

/*
** EXEC
*/
void			exec_simple(t_cli cli, t_builtin *b);
t_cmds			*exec_pipe(t_cmds *tmp, t_builtin *b);

/*
** Heredoc.c
*/
char			*heredoc(char *src, t_builtin *b);
/*
** Redirection
*/
int				ape(char **output);
int				wfile(char **output);
int				rfile(char **input);
int				doc(char **input, t_builtin *b);

/*
** Dollar_option.c
*/
void			special_char(char **str, t_builtin *b);

#endif
