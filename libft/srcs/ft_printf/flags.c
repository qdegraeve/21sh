#include "ft_printf.h"

void	check_flags(char *f, t_arg *a)
{
	while (f[a->i] == '-' || f[a->i] == '+' || f[a->i] == ' ' || f[a->i] == '#'
			|| f[a->i] == '0')
	{
		if (f[a->i] == '-')
			a->f_m = 1;
		if (f[a->i] == '+')
			a->f_p = 1;
		if (f[a->i] == ' ')
			a->f_sp = 1;
		if (f[a->i] == '#')
			a->f_h = 1;
		if (f[a->i] == '0')
			a->f_zero = 1;
		if (f[a->i + 1] != '\0')
			a->i++;
		else
			return ;
	}
	check_min_lenght(f, a);
}
