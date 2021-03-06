#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(s);
	if (!(new = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
