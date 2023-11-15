/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:01:52 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/15 19:17:37 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_free_tab(void **tab)
// {
// 	int	i;

// 	i = 0;
// 	if (tab)
// 	{
// 		while (tab[i])
// 		{
// 			free (tab[i]);
// 			i++;
// 		}
// 		free (tab[i]);
// 		free (tab);
// 	}
// }

void ft_free_tab(void **tab) {
    int i;

    if (tab) {
        for (i = 0; tab[i]; i++) {
            free(tab[i]);
        }
        free(tab);
    }
}
