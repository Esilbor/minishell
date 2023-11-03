/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:21:42 by bbresil           #+#    #+#             */
/*   Updated: 2023/05/10 19:56:37 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar2(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_fd2(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_format_converter(va_list args, char c)
{
	int	res;

	res = 0;
	if (c == 'c')
		res += ft_putchar2(va_arg(args, int));
	else if (c == 's')
		res += ft_putstr_fd2(va_arg(args, char *), 1);
	else if (c == 'p')
		res += ft_putptr(va_arg(args, unsigned long), "0123456789abcdef", 1);
	else if (c == 'd' || c == 'i')
		res += ft_putnbr_base(va_arg(args, int), "0123456789");
	else if (c == 'u')
		res += ft_putnbr_base_u(va_arg(args, unsigned int), "0123456789");
	else if (c == 'x')
		res += ft_putnbr_base_u(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		res += ft_putnbr_base_u(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		res += ft_putchar2('%');
	else
	{
		res += ft_putchar2('%');
		res += ft_putchar2((int)c);
	}
	return (res);
}

int	ft_printf(const char *str, ...)
{
	int		res;
	int		i;
	va_list	args;

	res = 0;
	i = 0;
	va_start(args, str);
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (!str[i + 1])
				return (-1);
			res += ft_format_converter(args, str[i + 1]);
			i++;
		}
		else
			res += ft_putchar2(str[i]);
		i++;
	}
	va_end(args);
	return (res);
}
