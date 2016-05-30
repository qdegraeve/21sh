/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:48 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:48 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"
# include "lexer.h"

/*
** PARSER
*/
void			parser(t_cmds **root, t_builtin *b);
char			**str_to_argv(char const *s);
void			clean_quote(char **line);

/*
** EXEC
*/
void			exec_simple(t_cmds *root, t_builtin *b);
t_cmds			*exec_pipe(t_cmds *tmp);
void			close_child_fd(t_cmds *root, int i, int nb, int fdes[][2]);
int				pipe_handler(t_cmds *tmp, t_builtin *b);

/*
** Heredoc.c
*/
char			*heredoc(char *src, t_builtin *b);
/*
** Redirection && AGGREGATION
*/
int				ape(char **output);
int				wfile(char **output);
int				rfile(char **input);
int				doc(char **input, t_builtin *b);
int				is_agregator(char *str);
int				ft_is_agregator(char *str);
int				redir_just_fd(char *str);
char			*go_to_file(char *str, int nb);
/*
** Dollar_option.c
*/
void			special_char(char **str, t_builtin *b);

#endif
