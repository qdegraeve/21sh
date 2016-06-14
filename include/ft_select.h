/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 11:41:04 by qdegraev          #+#    #+#             */
/*   Updated: 2016/06/14 13:18:21 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H

# define FT_SELECT_H

# include <shell.h>

typedef struct	s_env_select
{
	int			length;
	char		on;
	int			line;
	int			line_nbr;
	int			col;
	t_list		lst;
	int			up;
	int			fd;
	struct termios term;
}				t_env_select;

typedef struct	s_choice
{
	char		*arg;
	char		sel;
}				t_choice;

/*
**		main.c
*/
void			term_set_select();
void			term_reset_select(struct termios term);
void			del_choice(void *c, size_t content_size);
int				ft_select(char **argv);

/*
**		display.c
*/
void			display_choices(t_env_select *e);
void			move(t_env_select *e);
void			initial_position(t_env_select *e, int col);

/*
**		signals_select.c
*/
void			signal_catcher_select();
t_env_select	*get_env_select();

/*
**		keys.c
*/
void			get_input_select(t_env_select *e);
void			get_fd(t_env_select *e);

/*
**		actions.c
*/
void			chose_one(t_env_select *e);
void			remove_one(t_env_select *e);
int				selected(t_env_select *e, int input);

/*
**		tools.c
*/
void			liste_init(t_list *lst);
void			env_init_select(t_env_select *e);
void			del_choice(void *c, size_t content_size);

#endif
