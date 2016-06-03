#include "parser.h"

static int		ft_lenword(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] != ' ' && *s != '\t' && *s != '\n') ||
				(s[i] && s[i - 1] == 92) ||
				!command_ncomplete(get_quote(), (char*)s, i)))
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
	while (s && s[i])
	{
		if ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n') && check && s[i - 1]
				!= 92 && command_ncomplete(get_quote(), (char*)s, i))
			check = 0;
		else if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && check == 0)
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

static void		ft_split(char **new, const char *s)
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
		while (*s == ' ' || *s == '\t' || *s == '\n' || *s == 92)
			s++;
	}
	new[i] = NULL;
}

char			**str_to_argv(char const *s)
{
	char	**new;
	int		nbword;

	if (s == NULL)
		return (NULL);
	nbword = ft_countword(s);
	if (!nbword || !(new = ft_taballoc(nbword)))
		return (NULL);
	ft_split(new, s);
	return (new);
}
