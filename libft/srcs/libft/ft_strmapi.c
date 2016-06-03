#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*new;

	if (s == NULL || f == NULL)
		return (NULL);
	new = NULL;
	i = 0;
	len = ft_strlen(s);
	if (!(new = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
