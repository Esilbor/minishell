/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:47:12 by bbresil           #+#    #+#             */
/*   Updated: 2023/10/25 20:36:20 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putnbr_base_u(unsigned int nbr, char *base)
{
	unsigned int	base_nb;
	int				res;

	base_nb = ft_strlen2(base);
	res = 0;
	if (nbr < base_nb)
		res += ft_putchar2(base[nbr]);
	if (nbr >= base_nb)
	{
		res += ft_putnbr_base(nbr / base_nb, base);
		res += ft_putnbr_base(nbr % base_nb, base);
	}
	return (res);
}

int	ft_putnbr_base(int nbr, char *base)
{
	int	base_nb;
	int	res;
	int	min_int;

	base_nb = ft_strlen2(base);
	res = 0;
	min_int = -2147483648;
	if (nbr == min_int)
		return (ft_putstr_fd2("-2147483648", 1));
	if (nbr < 0)
	{
		res += ft_putchar2('-');
		nbr *= -1;
	}
	if (nbr < base_nb)
		res += ft_putchar2(base[nbr]);
	if (nbr >= base_nb)
	{
		res += ft_putnbr_base(nbr / base_nb, base);
		res += ft_putnbr_base(nbr % base_nb, base);
	}
	return (res);
}

int	ft_putptr(unsigned long ptr, char *base, int option)
{
	int			base_nb;
	int			res;

	base_nb = ft_strlen2(base);
	res = 0;
	if (option == 1 && !ptr)
		return (write(1, "(nil)", 5));
	if (option == 1)
		res += ft_putstr_fd2("0x", 1);
	if (ptr < (unsigned long) base_nb)
		res += ft_putchar2(base[ptr]);
	if (ptr >= (unsigned long) base_nb)
	{
		res += ft_putptr(ptr / base_nb, base, 0);
		res += ft_putptr(ptr % base_nb, base, 0);
	}
	return (res);
}
