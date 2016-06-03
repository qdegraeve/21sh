#include "ft_printf.h"

void	ft_putnbru(unsigned int nb)
{
	if (nb < 10)
	{
		ft_putchar(nb + 48);
		return ;
	}
	ft_putnbru(nb / 10);
	ft_putchar((nb % 10) + 48);
	return ;
}
