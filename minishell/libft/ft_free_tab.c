/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:01:52 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/10 14:56:00 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(void **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free (tab[i]);
			i++;
		}
		free(tab[i]);
		free (tab);
	}
}
