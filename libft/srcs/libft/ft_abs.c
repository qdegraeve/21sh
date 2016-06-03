#include "libft.h"

int		ft_abs(int i)
{
	return (i *= i < 0 ? -1 : 1);
}
