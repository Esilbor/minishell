/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esilbor <esilbor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:09:43 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/23 11:39:40 by esilbor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// finds little in big within len, returning its position or NULL
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (len == 0 && (!big || !little))
		return (NULL);
	i = 0;
	j = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && (i < len))
	{
		j = 0;
		while (((i + j) < len) && (little[j] == big[i + j]) && little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
