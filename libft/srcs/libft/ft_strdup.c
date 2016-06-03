#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;

	if (src == NULL)
		return (NULL);
	if (!(str = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(str, src);
	return (str);
}
