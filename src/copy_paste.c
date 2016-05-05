#include "shell.h"

void copy_paste_mod(t_env *e, int input, char *str)
{
	e = (void*)e;
	str += 1;
	if (input == CUT_OPT)
	{
		ft_printf("CUT MODE ENABLED");
	}
	else if (input == COPY_OPT)
	{
		ft_printf("COPY MODE ENABLED");
	}
	else if (input == PASTE_OPT)
	{
		ft_printf("PASTE MODE ENABLED");
	}
}
