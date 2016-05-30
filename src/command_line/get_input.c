/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:37 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 16:32:37 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_input(t_builtin *b, int input)
{
	int		ret;
	char	buf[8];
	t_env	*e;

	ret = -1;
	e = get_env();
	if (input == 10)
		tputs(tgetstr("up", NULL), 0, ft_putchar2);
	while (42)
	{
		ft_bzero(buf, 8);
		if (input == 10)
		{
			tputs(tgetstr("rc", NULL), 0, ft_putchar2);
			ft_putchar('\n');
			if (ret == 0)
				return (((t_history*)b->lst.tail->content)->command);
			else
				quote_prompt(get_env());
		}
		read(0, buf, 7);
		buf[7] = '\0';
		input = (buf[3] << 24) + (buf[2] << 16) + (buf[1] << 8) + buf[0];
		ret = edit_line(e, input, &b->lst);
	}
}
