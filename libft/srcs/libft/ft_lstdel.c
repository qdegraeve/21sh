#include "libft.h"

void		ft_lstdel(t_list *lst, void (*del)(void *, size_t))
{
	t_elem *tmp;
	t_elem *backup;

	if (lst == NULL || del == NULL)
		return ;
	tmp = lst->head;
	while (lst->length-- > 0)
	{
		backup = tmp->next;
		ft_lstdelone(lst, tmp, (*del));
		tmp = backup;
	}
	lst = NULL;
}
