/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:38 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:38 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*heredoc(char *src, t_builtin *b)
{
	char	*line;
	t_env	*e;

	line = NULL;
	init_env(e = get_env(), src);
	term_set();
	line = ft_strdup(get_input(b, 10));
	term_reset();
	if (line)
		ft_lstdelone(&b->lst, b->lst.tail, del_lst_char);
	return (line);
}
