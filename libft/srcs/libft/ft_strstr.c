#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (s2[i] == '\0')
		return (char*)(s1);
	while (s1[i] != '\0')
	{
		k = 0;
		while (s1[i + k] == s2[k])
		{
			k++;
			if (s2[k] == '\0')
				return (char*)(&s1[i]);
		}
		i++;
	}
	return (NULL);
}
