/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   agregator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 16:32:34 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/30 21:37:49 by nahmed-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_is_agregator(char *str)
{
	int		i;

	i = 0;
	while (ft_iswhitespace(str[i]) == 1)
		i++;
	str = &str[i];
	i = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		while (ft_isdigit(str[i]) == 1)
			i++;
		if (str[i] && (str[i] == '>' || str[i] == '<') && str[i + 1] == '&')
		{
			str = &str[i + 2];
			i = 0;
			if (ft_isdigit(str[0]) == 1)
				return (1);
			else if (str[0] == '-')
				return (1);
		}
	}
	return (0);
}

static int	redir(int input, char *str)
{
	int		i;
	int		output;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		while (ft_isdigit(str[i]) == 1)
			i++;
		output = ft_atoi(ft_strncpy(ft_strnew(i), str, i));
		dup2(output, input);
		return (1);
	}
	else if (str[0] == '-')
	{
		close(input);
		return (1);
	}
	return (0);
}

int			is_agregator(char *str)
{
	int		i;
	int		input;

	i = 0;
	while (ft_iswhitespace(str[i]) == 1)
		i++;
	str = &str[i];
	i = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		while (ft_isdigit(str[i]) == 1)
			i++;
		if (str[i] && (str[i] == '>' || str[i] == '<') && str[i + 1] == '&')
		{
			input = ft_atoi(ft_strncpy(ft_strnew(i), str, i));
			str = &str[i + 2];
			return (redir(input, str));
		}
	}
	return (0);
}

int			redir_just_fd(char *str)
{
	int		i;
	int		output;

	i = 0;
	while (ft_iswhitespace(str[i]) == 1)
		i++;
	str = &str[i];
	i = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		while (ft_isdigit(str[i]) == 1)
			i++;
		output = ft_atoi(ft_strncpy(ft_strnew(i), str, i));
		if (output >= 0 && output <= 255)
			return (output);
		else
		{
			ft_printf("%d : bad file descriptor\n", output);
			return (-1);
		}
	}
	return (STDOUT_FILENO);
}

char		*go_to_file(char *str, int nb)
{
	int		i;

	i = 0;
	while (ft_isdigit(str[i]) == 1)
		i++;
	if (nb == 1)
		i++;
	else if (nb == 2)
		i += 2;
	return (ft_strcpy(ft_strnew(i), &str[i]));
}
