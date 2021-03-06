#include "shell.h"

char		*ft_str_partsub(char *src, int start, int end, char *ins)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(src) - (end - start) + ft_strlen(ins);
	dest = ft_strnew(len);
	dest = ft_strncpy(dest, src, start);
	if (ins)
		dest = ft_strcat(dest, ins);
	dest = ft_strcat(dest, src + end);
	if (src)
		ft_strdel(&src);
	return (dest);
}

static int	dollar_char(char **str, t_builtin *b, int i)
{
	int		end;
	char	*ins;
	char	*tmp;

	end = i;
	ins = NULL;
	tmp = NULL;
	while ((*str)[end] && (*str)[end] != ' ' && (*str)[end] != '\t')
		end++;
	tmp = ft_strnew(end - i - 1);
	tmp = ft_strncpy(tmp, (*str) + i + 1, end - i - 1);
	ins = ft_getenv(tmp, b->env);
	*str = ft_str_partsub((*str), i, end, ins);
	return (ft_strlen(ins));
}

void		special_char(char **str, t_builtin *b)
{
	int		i;
	int		tilde;
	char	*ins;

	i = 0;
	tilde = 0;
	ins = NULL;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == 92)
			i += 2;
		else if ((*str)[i] == '~' && !tilde && (*str)[i + 1] &&
				(*str)[i + 1] != '~')
		{
			ins = ft_getenv("HOME", b->env);
			*str = ft_str_partsub((*str), i, i + 1, ins);
			i += ft_strlen(ins);
			tilde++;
		}
		else if ((*str)[i] == '$')
			i = dollar_char(str, b, i);
		else
			i++;
	}
}
