#include "libft.h"

void	ft_strdel(char **as)
{
	if (as == NULL || *as == NULL)
		return ;
	ft_memdel((void**)as);
}
