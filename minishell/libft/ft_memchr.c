/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:11:41 by bbresil           #+#    #+#             */
/*   Updated: 2022/11/28 15:24:21 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	u;
	size_t			i;

	i = 0;
	u = c;
	ptr_s = (unsigned char *)s;
	while (i < n)
	{
		if (ptr_s[i] == u)
			return (&ptr_s[i]);
		i++;
	}
	return (NULL);
}
