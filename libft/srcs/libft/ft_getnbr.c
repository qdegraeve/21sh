#include "libft.h"

int		ft_getnbr(char *str)
{
	int nb;
	int i;

	i = 0;
	nb = 0;
	if (str[0] == '-')
		return (-ft_getnbr(&str[1]));
	while (ft_isdigit(str[i]) == 1)
	{
		nb = (nb * 10) + (str[i] - '0');
		i++;
	}
	return (nb);
}
