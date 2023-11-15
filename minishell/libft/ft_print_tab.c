/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:43:35 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/15 12:13:55 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../ft_printf/ft_printf.h"
#include "libft.h"

void	ft_print_tab(void **tab, char *tab_name)
{
	int	j;

	j = 0;
	if (tab)
	{
		while (tab[j])
		{
			ft_printf("%s[%d] = %s\n", tab_name, j, (char *)tab[j]);
			j++;
		}
		ft_printf("\n");
	}
	else
		ft_printf("(NULL)\n");
}
