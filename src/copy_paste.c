#include "shell.h"


static void cut(t_env *e, char *str, t_builtin *b)
{
	str += 1;
	e = (void*)e;
}

static void copy(t_env *e, char *str, t_builtin *b)
{
	
}

static void paste(t_env *e, char *str, t_builtin *b)
{
	str += 1;
	e = (void*)e;
}

void copy_paste_mod(t_env *e, int input, char *str)
{
	if (input == CUT_OPT)
		cut(e, str, get_buil());
	else if (input == COPY_OPT)
		copy(e, str, get_buil());
	else if (input == PASTE_OPT)
		paste(e, str, get_buil());
}
