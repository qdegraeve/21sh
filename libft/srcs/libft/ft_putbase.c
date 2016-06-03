#include "libft.h"

void	ft_putbase(unsigned int n, unsigned int base)
{
	unsigned int	tmp;

	if (n >= base)
		ft_putbase(n / base, base);
	else
	{
		if (base == 8)
			ft_putchar('0');
		else if (base == 16)
			ft_putstr("0x");
	}
	tmp = n % base;
	if (tmp <= 9)
		ft_putchar(tmp + '0');
	else if (tmp > 9 && tmp <= 9 + 26)
		ft_putchar(tmp + 'A' - 10);
}
