/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afillion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 14:04:50 by afillion          #+#    #+#             */
/*   Updated: 2016/04/27 20:26:12 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

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

void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char*));
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
char				*ft_strmap(char const *s, char (*f)(char));
int					ft_strequ(const char *s1, const char *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strnequ(const char *s1, const char *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_cjoin(char *s1, char *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
void				ft_putbase(unsigned int n, unsigned int base);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_iswhitespace(char c);
int					ft_abs(int i);

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_elem				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list *lst, t_elem **alst,
		void (*del)(void *, size_t));
void				ft_lstdel(t_list *lst, void (*del)(void *, size_t));
void				ft_lstadd(t_elem **alst, t_elem *new);
void				ft_lstiter(t_elem *lst, void (*f)(t_elem *elem));
t_elem				*ft_lstmap(t_elem *lst, t_elem *(*f)(t_elem *elem));
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
int		ft_lstinsert(t_list *lst, void *content, int content_size, int pos);

#endif
