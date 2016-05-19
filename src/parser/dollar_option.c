#include	"shell.h"

char	*ft_str_partsub(char *src, int start, int end, char *ins)
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

void	replace_dollar(char **str, t_builtin *b)
{
	int		i;
	int		end;
	char	*ins;
	char	*tmp;

	i = 0;
	ins = NULL;
	tmp = NULL;
	end = 0;
	while (*str && (*str)[i])
	{
		if ((*str)[i] == 92)
			i += 2;
		else if ((*str)[i] == '~')
		{
			tmp = ft_getenv("HOME", b->env);
			*str = ft_str_partsub((*str), i, i + 1, tmp);
			i += ft_strlen(tmp);
		}
		else if ((*str)[i] == '$')
		{
			end = i;
			while ((*str)[end] && (*str)[end] != ' ' && (*str)[end] != '\t')
				end++;
			ins = ft_strnew(end - i - 1);
			ins = ft_strncpy(ins, (*str) + i + 1, end - i - 1);
			tmp = ft_getenv(ins, b->env);
			*str = ft_str_partsub((*str), i, end, tmp);
			i += ft_strlen(tmp);
		}
		else
			i++;
	}
}
