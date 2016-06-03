#include "libft.h"

void		ft_lstiter(t_elem *lst, void (*f)(t_elem *elem))
{
	t_elem	*backup;

	if (lst == NULL || f == NULL)
		return ;
	while (lst)
	{
		backup = lst->next;
		f(lst);
		lst = backup;
	}
}
