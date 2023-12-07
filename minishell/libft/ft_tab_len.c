/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:46:38 by bbresil           #+#    #+#             */
/*   Updated: 2023/12/07 07:31:19 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//return the lenght of a NULL-terminated char**
int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
