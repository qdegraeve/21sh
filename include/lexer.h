/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:47 by qdegraev          #+#    #+#             */
/*   Updated: 2016/06/02 12:33:01 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

typedef struct		s_io
{
	char		*io;
	struct s_io *next;
}					t_io;

typedef struct		s_cmds
{
	char			*cmd;
	int				pipe;
	int				AND;
	int				OR;
	t_io			*input;
	t_io			*output;
	char			**tab_i;
	char			**tab_o;
	struct s_cmds	*next;
}					t_cmds;

/*
** Tools
*/
void				add_cmds(char *str, int pipe, t_cmds **root);
void				add_io(char *str, t_cmds **root, int fd);
int					space_priority(char *str);
int					get_io(char *str);
void				count(int *i, int *total, int counter);
void				del_lex_io(t_cmds **root);

/*
** LEXER
*/
t_cmds				*lexer(char *str);
int					add_all_io(t_cmds **root, char *str);
int					get_priority(char *str);
t_quote				*get_quote(void);

/*
** TOUCH FUNCTION
*/
void				io_to_argv(t_cmds *root, int nb);
void				touch_file(char *str);
#endif
