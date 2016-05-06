#include "shell.h"

static void cut(t_env *e, char *str)
{
	str += 1;
	e = (void*)e;
}

static void copy(t_env *e, char *str, t_builtin *b)
{
	if (b->paste)
		ft_strdel(&b->paste);
	if (ft_strlen(str) > 0)
		b->paste = ft_strdup(&str[e->curs_pos]);
}

static void paste(t_env *e, char *str, t_builtin *b, t_elem **elem)
{
	char	*dest;
	int		len;
	int		i = 0;

	if ((*elem)->next == NULL)
		i = 1;
	if (!b->paste)
		return ;
	len = ft_strlen(str) + ft_strlen(b->paste);
	dest = ft_strnew(len);
	dest = ft_strncpy(str, dest, e->curs_pos);
	dest = ft_strcat(dest, b->paste);
	if (e->curs_pos < e->curs_max)
		dest = ft_strcat(dest, b->paste + e->curs_pos);
	dest[len + 1] = '\0';
//	while (dest[i] != '\0')
//		write_char(e, dest[i++], *elem);
}

void copy_paste_mod(t_env *e, int input, char *str, t_elem **elem)
{
	if (input == CUT_OPT)
		cut(e, str);
	else if (input == COPY_OPT)
		copy(e, str, get_buil());
	else if (input == PASTE_OPT)
		paste(e, str, get_buil(), elem);
}
