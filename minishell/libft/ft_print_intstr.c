/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_intstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:59:01 by bbresil           #+#    #+#             */
/*   Updated: 2023/06/19 08:48:34 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"

void	ft_print_intstr(int *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		ft_printf("%d\n", str[j]);
		j++;
	}
	ft_printf("\n");
}
