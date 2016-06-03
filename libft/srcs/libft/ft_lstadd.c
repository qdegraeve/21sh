#include "libft.h"

void		ft_lstadd(t_elem **alst, t_elem *to_add)
{
	if (alst == NULL || to_add == NULL)
		return ;
	to_add->next = *alst;
	*alst = to_add;
}
