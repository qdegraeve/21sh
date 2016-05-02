/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:15:14 by qdegraev          #+#    #+#             */
/*   Updated: 2016/05/02 14:24:36 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include	"libft.h"

typedef struct		s_elem
{
	void			*content;
	size_t			content_size;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct		s_list
{
	int				length;
	struct s_elem	*head;
	struct s_elem	*tail;
}					t_list;

void				ft_lstdel(t_list *lst, void (*del)(void *, size_t));
void				ft_lstadd(t_elem **alst, t_elem *to_add);
void				ft_lstiter(t_elem *lst, void (*f)(t_elem *elem));
t_elem				*ft_lstmap(t_elem *lst, t_elem *(*f)(t_elem *elem));
t_elem				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list *lst, t_elem **alst,
									void (*del)(void *, size_t));
void				ft_lstadd_back(t_elem **beg_lst, void const *content,
									size_t cont_size);
int					ft_lstadd_last(t_list *lst, void const *content,
									size_t content_size);
int					ft_lstadd_first(t_list *lst, void const *content,
									size_t cont_size);
int					ft_lstadd_first_circ(t_list *lst, void const *content,
									size_t cont_size);
int					ft_lstadd_last_circ(t_list *lst, void const *content,
									size_t cont_size);
int					ft_lstinsert(t_list *lst, void *content, int content_size,
									int pos);

#endif
