#include "libft.h"

char	*ft_cjoin(char *s1, char *s2)
{
	char	*stock;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	stock = ft_strjoin(s1, s2);
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	return (stock);
}