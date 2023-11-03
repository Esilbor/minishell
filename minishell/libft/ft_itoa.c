/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:04:29 by bbresil           #+#    #+#             */
/*   Updated: 2023/02/27 13:01:51 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			intlen;
	char		*str;

	nb = n;
	intlen = ft_intlen(nb);
	str = malloc(sizeof(char) * (intlen + 1));
	if (!str)
		return (NULL);
	str[intlen] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0 && intlen > 0)
	{
		str[intlen - 1] = (nb % 10) + 48;
		nb /= 10;
		intlen --;
	}
	return (str);
}
