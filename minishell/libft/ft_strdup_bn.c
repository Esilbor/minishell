/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbresil <bbresil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:07:21 by bbresil           #+#    #+#             */
/*   Updated: 2023/07/06 11:13:45 by bbresil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// add a backslash n at the end of the returned str

char	*ft_strdup_bn(const char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(const char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\n';
	str[i + 1] = '\0';
	return (str);
}
