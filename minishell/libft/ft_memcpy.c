/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:37:04 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/08 11:31:20 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Copies `n` bytes from `src` to `dest`, returns `dest`, NULL if both are NULL
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*str_src;
	char		*str_dest;

	if (!dest && !src)
		return (NULL);
	i = 0;
	str_src = src;
	str_dest = dest;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		i++;
	}
	return (dest);
}
