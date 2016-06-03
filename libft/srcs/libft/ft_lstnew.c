#include "libft.h"

t_elem		*ft_lstnew(void const *content, size_t content_size)
{
	t_elem		*new;

	new = NULL;
	if (!(new = (t_elem*)malloc(sizeof(t_elem))))
		return (NULL);
	ft_bzero(new, sizeof(t_elem));
	new->content_size = 0;
	new->content = NULL;
	if (content == NULL)
		return (new);
	else
	{
		new->content_size = content_size;
		if (!(new->content = malloc(content_size)))
			return (NULL);
		ft_bzero(new->content, content_size);
		ft_memcpy(new->content, content, content_size);
	}
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
