#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	if (c < 0 || c > 255 || c == '\0')
		return (char*)(s + i);
	while (s[i] != (char)c && i > 0)
		i--;
	if (i <= 0)
		return (NULL);
	return (char*)(s + i);
}
