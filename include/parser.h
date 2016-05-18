#ifndef PARSER_H
# define PARSER_H

#include "shell.h"
#include "lexer.h"
/*
** PARSER
*/
void	parser(t_cmds **root);
char **str_to_argv(char const *s);

/*
** EXEC
*/
void	exec_simple(t_cmds *cmd);
#endif
