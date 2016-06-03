#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t			i;
	unsigned int	start;
	unsigned int	end;

	i = 0;
	start = 0;
	end = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	start = i;
	while (s[i] != '\0')
	{
		if (s[i] >= '!' && s[i] <= '~')
			end = i;
		i++;
	}
	if (end == 0)
		return (ft_strnew(1));
	return (ft_strsub(s, start, (size_t)(end - start + 1)));
}
