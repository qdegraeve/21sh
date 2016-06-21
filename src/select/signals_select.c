/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 13:00:34 by qdegraev          #+#    #+#             */
/*   Updated: 2016/06/21 11:41:17 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_env_select	*get_env_select(void)
{
	static t_env_select *stat_e = NULL;

	if (!stat_e)
	{
		if (!(stat_e = (t_env_select*)malloc(sizeof(t_env_select))))
			return (NULL);
		ft_bzero(stat_e, sizeof(t_env_select));
	}
	return (stat_e);
}

void			resize_select(int sig)
{
	if (sig == SIGWINCH)
	{
		display_choices(get_env_select());
		signal(SIGWINCH, resize);
	}
}

void			signal_catcher_select(void)
{
	int i;

	i = 0;
	signal(SIGWINCH, resize);
}
