#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int j;

	i = ft_strlen(dest);
	j = 0;
	if (src)
	{
		while (src[j])
		{
			dest[i + j] = src[j];
			j++;
		}
		dest[i + j] = '\0';
	}
	return (dest);
}
