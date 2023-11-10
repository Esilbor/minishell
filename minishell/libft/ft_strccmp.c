/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:28:16 by bbresil           #+#    #+#             */
/*   Updated: 2023/11/10 16:18:48 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Compares string s1 to char c, returns 0 if all chars in s1 are c
int	ft_strccmp(const char *s1, char c)
{
	unsigned char	*str1;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	while (str1[i] && str1[i] == c)
		i++;
	if (i == ft_strlen(s1))
		return (0);
	return (1);
}
