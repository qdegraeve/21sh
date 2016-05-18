#include "parser.h"


static int		ft_lenword(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && !command_ncomplete(get_quote(), (char*)s, i))
		i++;
	return (i);
}

static int		ft_countword(const char *s)
{
	int	nb;
	int	i;
	int	check;

	i = 0;
	check = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] == ' ' && check && command_ncomplete(get_quote(), (char*)s, i))
			check = 0;
		else if (s[i] != ' ' && !check)
		{
			nb++;
			check++;
		}
		i++;
	}
	return (nb);
}

static char		**ft_taballoc(int nbword)
{
	char	**new;

	if (!(new = (char**)malloc((nbword + 1) * sizeof(*new))))
		return (NULL);
	new[0] = NULL;
	return (new);
}

static void		ft_split(char **new, const char *s, char c)
{
	int		i;
	char	*word;
	int		lenword;

	i = 0;
	while (*s != '\0')
	{
		lenword = ft_lenword(s);
		if (lenword != 0)
		{
			word = ft_strsub(s, 0, lenword);
			new[i] = word;
			i++;
		}
		s += lenword;
		while (*s == c)
			s++;
	}
	new[i] = NULL;
}

char			**custom_ft_strsplit(char const *s, char c)
{
	char	**new;
	int		nbword;

	if (s == NULL)
		return (ft_taballoc(0));
	nbword = ft_countword(s);
	if (!(new = ft_taballoc(nbword)))
		return (NULL);
	ft_split(new, s, c);
	return (new);
}
