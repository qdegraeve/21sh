#include "libft.h"

void	ft_lstadd_back(t_elem **beg_lst, void const *content, size_t cont_size)
{
	t_elem	*new;
	t_elem	*tmp;

	new = NULL;
	tmp = NULL;
	if (!(new = ft_lstnew(content, cont_size)))
		return ;
	if (!(*beg_lst))
		*beg_lst = new;
	else
	{
		tmp = *beg_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}
