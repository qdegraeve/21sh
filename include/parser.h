#ifndef PARSER_H
# define PARSER_H

#include "shell.h"
#include "lexer.h"
/*
** PARSER
*/
void	parser(t_cmds **root);
char **custom_ft_strsplit(char const *s, char c);

/*
** EXEC
*/
void	exec_simple(t_cmds *cmd);
#endif
