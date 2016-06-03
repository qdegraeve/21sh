#include "libft.h"

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nb > 2147483647)
		return ;
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar('-');
	}
	if (nb < 10)
	{
		ft_putchar(nb + 48);
		return ;
	}
	ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + 48);
	return ;
}
