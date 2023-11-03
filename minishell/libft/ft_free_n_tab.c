/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_n_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:16:42 by bbresil           #+#    #+#             */
/*   Updated: 2023/07/14 10:19:36 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// free n first elements of a tab (usefull id !tab[0] but tab[1])
void	ft_free_n_tab(void **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free (tab[i]);
		i++;
	}
	free (tab[i]);
	free (tab);
}
