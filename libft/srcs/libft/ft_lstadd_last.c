#include "libft.h"

int		ft_lstadd_last(t_list *lst, void const *content, size_t cont_size)
{
	t_elem	*new;

	new = NULL;
	if (!(new = ft_lstnew(content, cont_size)))
		return (-1);
	if (lst->length == 0)
	{
		lst->tail = new;
		lst->head = new;
		lst->length++;
	}
	else
	{
		lst->tail->next = new;
		new->prev = lst->tail;
		lst->tail = new;
		lst->length++;
	}
	return (0);
}
