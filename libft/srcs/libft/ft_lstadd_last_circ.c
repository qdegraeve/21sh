#include "libft.h"

int		ft_lstadd_last_circ(t_list *lst, void const *content, size_t cont_size)
{
	t_elem	*new;

	new = NULL;
	if (!(new = ft_lstnew(content, cont_size)))
		return (-1);
	if (lst->length == 0)
	{
		new->next = new;
		new->prev = new;
		lst->tail = new;
		lst->head = new;
		lst->length++;
	}
	else
	{
		new->next = lst->head;
		new->prev = lst->tail;
		lst->tail->next = new;
		lst->tail = new;
		lst->head->prev = lst->tail;
		lst->length++;
	}
	return (0);
}
