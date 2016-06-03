#include "ft_printf.h"

void	type_f(t_arg *a)
{
	char *f;

	f = ft_dtoa_base(va_arg(a->ap, double), 10, a->p, a);
	a->ret = ft_strlen(f);
	ft_putstr(f);
}
