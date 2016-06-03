#include "ft_printf.h"

void	type_percent(t_arg *a)
{
	a->ret = 1;
	a->f_m == 1 ? ft_putchar('%') : 0;
	while (a->ret < a->l)
	{
		a->f_zero && !a->f_m ? ft_putchar('0') : ft_putchar(' ');
		a->ret++;
	}
	a->f_m == 0 ? ft_putchar('%') : 0;
}
